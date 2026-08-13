#include "stm32h7xx_hal.h"
#include "CompositionRoot.hpp"
#include "AxiSram_storage.hpp"
#include "Dtcm_storage.hpp"
#include "RingBuffer.hpp"
#include "MidiIOConfig.hpp"
#include "I2SBufferMemoryAccessor.hpp"
#include "I2SDmaBufferStorage.hpp"
#include "NoteStatePool.hpp"
#include "MidiEventGenerator.hpp"
#include "BandLimitedWaveTables.hpp"
#include "WaveOutputService.hpp"
#include "InputMidiSignalUseCase.hpp"
#include "MidiEventDispatchUseCase.hpp"
#include "MidiEventGeneratUseCase.hpp"
#include "AudioOutUseCase.hpp"
#include "MX_Initialization.hpp"
#include "WaveTableGenerators.hpp"

#include "Shared_Storage.hpp"
#include "SharedMemoryAccessor.hpp"
#include "SharedADSRStorage.hpp"
#include "SharedMsgBufferStorage.hpp"
#include "MsgEventDispatcher.hpp"
#include "MsgEventReceiver.hpp"
#include "UpdateADSRUseCase.hpp"
#include "MsgDispatcherInitialization.hpp"


namespace Composition
{
	extern "C"
	{
		I2S_HandleTypeDef hi2s1;
		DMA_HandleTypeDef hdma_spi1_tx;
	    UART_HandleTypeDef huart3;
	}
	Core::RingBuffer<uint8_t,Application::Config::MidiInputRingBufferSize> g_MidiSignalRingBuffer;

	// Infrastructure
	Infrastructure::I2S::I2SBufferMemoryAccessor g_I2SBufAccessor(Infrastructure::Memory::I2S_Buffer);
	Infrastructure::I2S::I2SDmaBufferStorage g_I2SDmaBuf(&hi2s1,g_I2SBufAccessor);

	// Domain
	Domain::Pool::NoteStatePool g_NoteStatePool(Infrastructure::Memory::dtcm_blNoteActive,Infrastructure::Memory::dtcm_NoteStatePods);
	Domain::Midi::MidiEventGenerator g_MidiEentGenerator;
	Domain::WaveTable::BandLimitedWaveTables g_BandLimitedWaveTables(Infrastructure::Memory::dtcm_waveTablePods);
	Domain::Service::WaveOutputService g_WaveOutputService(g_NoteStatePool,g_BandLimitedWaveTables,Infrastructure::Memory::dtcm_ADSRParamPod);
	Domain::Service::UpdateADSRParameterService g_UpdateADSRParameterService(Infrastructure::Memory::dtcm_ADSRParamPod);

	// Application
	Application::UseCase::Midi::InputMidiSignalUseCase g_InputMidiSignalUseCase(g_MidiSignalRingBuffer);
	Application::UseCase::Midi::MidiEventDispatchUseCase g_MidiEventDispatchUseCase(g_NoteStatePool,g_BandLimitedWaveTables);
	Application::UseCase::Midi::MidiEventGeneratUseCase g_MidiEventGeneratUseCase(g_MidiSignalRingBuffer,g_MidiEentGenerator,g_MidiEventDispatchUseCase);

	using I2SStorage = Infrastructure::I2S::I2SDmaBufferStorage;
	Application::UseCase::Audio::AudioOutUseCase<I2SStorage> g_AudioOutUseCase(g_WaveOutputService,g_I2SDmaBuf);


	Infrastructure::SharedMemory::SharedMemoryAccessor sharedMemoryAccessor(&Infrastructure::Memory::shared_Adsr,&Infrastructure::Memory::shared_EventBuffer);
	Infrastructure::SharedMemory::SharedMsgBufferStorage sharedMsgBufStorage(sharedMemoryAccessor);
	Infrastructure::SharedMemory::SharedADSRStorage sharedADSRStorage(sharedMemoryAccessor);
	Application::Event::MsgEventDispatcher msgEventDispatcher;
	Application::UseCase::UpdateParameter::UpdateADSRUseCase<Infrastructure::SharedMemory::SharedADSRStorage> updateADSRUseCase(sharedADSRStorage,g_UpdateADSRParameterService);
	Infrastructure::Event::MsgEventReceiver msgEventReceiver(sharedMsgBufStorage,msgEventDispatcher);

	// PURPOSE:
	// STM32CubeMXの自動生成関数群を呼び出す処理
	// 起動時の初期化処理として実行する関数
	void MX_Initialization()
	{
		/* Initialize all configured peripherals */
		Initialization::MX_Initialization::MX_GPIO_Init();
		Initialization::MX_Initialization::MX_DMA_Init();
		Initialization::MX_Initialization::MX_I2S_Init(hi2s1);
		Initialization::MX_Initialization::MX_USART3_UART_Init(huart3);
		Initialization::MsgDispatcherInitialization::init(msgEventDispatcher, updateADSRUseCase);
	}

	void I2STransmitStart()
	{
		g_I2SDmaBuf.start();
	}

	void UARTReceiveStart()
	{
		HAL_UART_Receive_IT(&huart3, &Infrastructure::Memory::UART_RxByte, 1);
	}

	void WaveTableInitialization()
	{
		g_BandLimitedWaveTables.generateWaveTable(Domain::WaveTable::createSinWave);
	}

	// PURPOSE:
	// 起動時に各コンポジションの初期化処理として実行する関数
	// WAY:
	// M4コア側でメモリ初期化が完了するまでの間に共有メモリを触るとM4コア側が停止するため
	// 頭に500msのスリープ入れて回避している
	// ORDER:
	// MX_InitializationでI2SやUARTの基本設定を先に実行する必要がある
	void CompositInitialization()
	{
		HAL_Delay(500);
		//__SEV();
		MX_Initialization();
		I2STransmitStart();
		UARTReceiveStart();
		WaveTableInitialization();

		Infrastructure::Memory::dtcm_ADSRParamPod.m_attackTime = 0.1;
		Infrastructure::Memory::dtcm_ADSRParamPod.m_decayTime = 0.1;
		Infrastructure::Memory::dtcm_ADSRParamPod.m_sustainLevel = 0.1;
		Infrastructure::Memory::dtcm_ADSRParamPod.m_sustainLevel = 0.1;
		Infrastructure::Memory::dtcm_ADSRParamPod.m_sustainLevel = 0.1;
	}

	Infrastructure::Event::MsgEventReceiver& GetMsgEventReceiver() {return msgEventReceiver;}
	Infrastructure::I2S::I2SDmaBufferStorage& GetAudioOutBuffer(){return g_I2SDmaBuf;}
	Application::UseCase::Audio::AudioOutUseCase<I2SStorage>& GetAudioOutUseCase(){return g_AudioOutUseCase;}
	Application::UseCase::Midi::InputMidiSignalUseCase& GetInputMidiSignalUseCase(){return g_InputMidiSignalUseCase;}
	Application::UseCase::Midi::MidiEventGeneratUseCase& GetMidiEventGeneratUseCase(){return g_MidiEventGeneratUseCase;}
	uint8_t* GetUARTRxByte(){return &Infrastructure::Memory::UART_RxByte;}

}
