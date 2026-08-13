#pragma once
#include <stdint.h>
#include <variant>
#include "NoteStatePool.hpp"
#include "BandLimitedWaveTables.hpp"
#include "MidiEventTypes.hpp"

using namespace Domain;

namespace Application::UseCase::Midi
{
	// PURPOSE:
	// Midiイベントの種類に応じて対応する関数をディスパッチするクラス
	// WAY:
	// 現状は NoteOn / NoteOff のみを扱うため、本クラス内に処理を集約している
	// 将来的にイベント種類が増えた場合は、クラス責務分散のためにイベントごとにUseCaseを分離する
	// HOW:
	// MidiEventGeneratUseCaseでイベント生成がされた後にこのクラスのexecuteが呼ばれる
	class MidiEventDispatchUseCase
	{
	public:
		MidiEventDispatchUseCase(Pool::NoteStatePool& pool, WaveTable::BandLimitedWaveTables& wavetable);
		void execute(EventData & eventData);
	private:
		Pool::NoteStatePool& m_NoteStatePool;
		WaveTable::BandLimitedWaveTables& m_WaveTable;
		void on_setEventNoteOn(NoteOnEventPod& eventData);
		void on_setEventNoteOff(NoteOffEventPod& eventData);

	};
}
