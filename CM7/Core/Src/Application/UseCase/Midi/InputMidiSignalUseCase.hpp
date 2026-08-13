#pragma once
#include "RingBuffer.hpp"
#include "MidiIOConfig.hpp"

using namespace Application::Config;

namespace Application::UseCase::Midi
{
	// PURPOSE:
	// 受信したMidi信号をキューにセットするユースケースクラス
	// HOW:
	// Midi受信時の割り込み関数にてexecuteを実行する
	// SCOPE:
	// キューのセットのみで信号解析は実行しない
	class InputMidiSignalUseCase
	{
	public:
		explicit InputMidiSignalUseCase(Core::RingBuffer<uint8_t,MidiInputRingBufferSize>& buf) :m_ringBuf(buf) {}
		bool execute(uint8_t signal);
	private:
		Core::RingBuffer<uint8_t,MidiInputRingBufferSize>& m_ringBuf;
	};
}

#include "InputMidiSignalUseCase_Impl.hpp"
