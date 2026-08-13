#include "CompositionRoot.hpp"
#include "ADSRView.hpp"
#include "Shared_Storage.hpp"
#include "SSD1306DisplayDriver.hpp"
#include "SharedMemoryAccessor.hpp"
#include "SharedADSRStorage.hpp"
#include "ADSRPresenter.hpp"
#include "UpdateADSRUseCase.hpp"
#include "ADSRViewController.hpp"
#include "StaticQueue.hpp"
#include "ButtonEventDispatcher.hpp"
#include "ButtonEventId.hpp"
#include "ButtonDispatcherInitialization.hpp"
#include "ButtonEventMonitor.hpp"
#include "MsgEventDispatcher.hpp"
#include "ADSRSpecProvider.hpp"
#include "ADSRParamInitialization.hpp"
#include "MX_Initialization.hpp"


namespace Composition
{

	static Infrastructure::SSD1306Driver::SSD1306DisplayDriver displayDriver;
	static Infrastructure::SharedMemory::SharedMemoryAccessor sharedMemory(&Infrastructure::Memory::shared_Adsr,&Infrastructure::Memory::shared_EventBuffer);
	static Infrastructure::SharedMemory::SharedADSRStorage sharedADSRStorage(sharedMemory);
	static Infrastructure::SharedMemory::SharedMsgBufferStorage sharedMsgBufStorage(sharedMemory);
	static Infrastructure::Event::MsgEventSender msgEventSender(sharedMsgBufStorage);

	static Core::StaticQueue<Domain::Event::ButtonEventId,32> eventButtonQueue;
	static Application::Event::ButtonEventDispatcher buttonEventDispatcher;
	static Infrastructure::Event::ButtonEventMonitor buttonEventMonitor(buttonEventDispatcher,eventButtonQueue);

	static Infrastructure::Input::Button::ButtonDebouncer buttonDebouncer;

	static ADSRView_t adsrView(displayDriver);
	static ADSRPresenter_t adsrPresenter(adsrView);

	static UpdateADSRUseCase_t updateADSRUseCase(sharedADSRStorage,adsrPresenter,msgEventSender);
	static ADSRViewController_t adsrViewController(updateADSRUseCase,adsrPresenter);
	static ADSRSpecProvider_t adsrSpecPresenter(adsrViewController);
	static UpdateADSRSpecUseCase_t updateADSRSpecUseCase(adsrSpecPresenter);


	ADSRView_t& GetADSRView() {return adsrView;}
	ADSRViewController_t& GetADSRViewController() {return adsrViewController;}
	Application::Event::ButtonEventDispatcher& GetButtonEventDispatcher() {return buttonEventDispatcher;}
	Core::StaticQueue<Domain::Event::ButtonEventId,32>& GetEventButtonQueue() {return eventButtonQueue;}
	Infrastructure::SSD1306Driver::SSD1306DisplayDriver& GetDisplayDriver() {return displayDriver;}
	Infrastructure::Event::ButtonEventMonitor& GetButtonEventMonitor() {return buttonEventMonitor;}
	Infrastructure::Input::Button::ButtonDebouncer& GetButtonDebouncer(){return buttonDebouncer;};

	// PURPOSE:
	// STM32CubeMXの自動生成関数群を呼び出す処理
	// 起動時の初期化処理として実行する関数
	void MX_Initialization()
	{
		Composition::Initialization::MX_Initialization::MX_DMA_Init();
		Composition::Initialization::MX_Initialization::MX_GPIO_Init();
		Composition::Initialization::MX_Initialization::MX_I2C1_Init();
	}

	// PURPOSE:
	// 起動時に各コンポジションの初期化処理として実行する関数
	// ORDER:
	// ディスプレイと共有メモリの初期化はADSRパラメータの初期化よりも先に実行される必要がある
	// ADSRパラメータ初期化の中で共有メモリのADSRパラメータ更新とディスプレイ更新処理が実行されるため
	void CompositInitialization()
	{
		displayDriver.init();
		sharedADSRStorage.sharedMemoryInitialization();
		sharedMsgBufStorage.sharedMemoryInitialization();
		Composition::Initialization::ButtonDispatcherInitialization::init(buttonEventDispatcher, adsrViewController);
		Composition::Initialization::ADSRParamInitialization::init(updateADSRSpecUseCase,updateADSRUseCase);
	}
}
