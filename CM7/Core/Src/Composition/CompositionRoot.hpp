#pragma once
#include "I2SDmaBufferStorage.hpp"
#include "InputMidiSignalUseCase.hpp"
#include "MidiEventGeneratUseCase.hpp"
#include "AudioOutUseCase.hpp"

#include "MsgEventReceiver.hpp"
#include "MsgEventDispatcher.hpp"

namespace Composition
{
	using I2SStorage = Infrastructure::I2S::I2SDmaBufferStorage;

	void CompositInitialization();
	Infrastructure::Event::MsgEventReceiver& GetMsgEventReceiver();
	Infrastructure::I2S::I2SDmaBufferStorage& GetAudioOutBuffer();
	Application::UseCase::Audio::AudioOutUseCase<I2SStorage>& GetAudioOutUseCase();
	Application::UseCase::Midi::InputMidiSignalUseCase& GetInputMidiSignalUseCase();
	Application::UseCase::Midi::MidiEventGeneratUseCase& GetMidiEventGeneratUseCase();
	uint8_t* GetUARTRxByte();
}
