#pragma once
#include "MidiEventGenerator.hpp"
#include "MidiEventDispatchUseCase.hpp"
#include "RingBuffer.hpp"
#include "MidiIOConfig.hpp"

using namespace Application::Config;
using namespace Domain::Midi;

namespace Application::UseCase::Midi
{
	// PURPOSE:
	// Midi信号を解析しMidiイベントを生成するユースケースクラス
	// HOW:
	// リングバッファからMidi信号を取得しイベント生成をする
	// SCOPE:
	// Midiイベントの生成までを実行してその後のイベント処理はディスパッチャで割り振る
	// CONSTRAINT:
	// 処理負荷が高いため割り込みコンテキストでは実行してはならない
	class MidiEventGeneratUseCase
	{
	public:
		MidiEventGeneratUseCase() = delete;
		MidiEventGeneratUseCase(
				Core::RingBuffer<uint8_t,MidiInputRingBufferSize>& buf,
				MidiEventGenerator& generator,
				MidiEventDispatchUseCase& dispatcher);
		void execute();
	private:
		Core::RingBuffer<uint8_t,MidiInputRingBufferSize>& m_ringBuf;
		MidiEventGenerator& m_midiEventGenerator;
		MidiEventDispatchUseCase& m_midiEventDispatchUseCase;
	};
}
