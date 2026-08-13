#include "MidiEventDispatchUseCase.hpp"
#include "NoteMath.hpp"

namespace Application::UseCase::Midi
{
	template<class... Ts>
	struct Overloaded : Ts...
	{
		using Ts::operator()...;
	};

	MidiEventDispatchUseCase::MidiEventDispatchUseCase(Pool::NoteStatePool& pool, WaveTable::BandLimitedWaveTables& wavetable):m_NoteStatePool(pool), m_WaveTable(wavetable){};

	template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;
	void MidiEventDispatchUseCase::execute(EventData& eventData)
	{
		std::visit(Overloaded{
			[](std::monostate mono) {},
			[&](NoteOnEventPod& noteon) { on_setEventNoteOn(noteon); },
			[&](NoteOffEventPod& noteoff) { on_setEventNoteOff(noteoff); },
			[](ErrResult& err) {}
			}, eventData);
	}


	void MidiEventDispatchUseCase::on_setEventNoteOn(NoteOnEventPod& eventData)
	{
		float freq = Domain::Note::NoteKeyToFrequency(eventData.m_noteKey);
		WaveTable::TableIndexCache tableIndexCache = m_WaveTable.createTableIndexCache(freq);
		m_NoteStatePool.createNoteState(eventData,tableIndexCache);
	}

	void MidiEventDispatchUseCase::on_setEventNoteOff(NoteOffEventPod& eventData)
	{
		m_NoteStatePool.noteoff(eventData);
	}
}
