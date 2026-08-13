#include "MidiEventGeneratUseCase.hpp"
#include <stdint.h>

namespace Application::UseCase::Midi
{
	MidiEventGeneratUseCase::MidiEventGeneratUseCase(
						Core::RingBuffer<uint8_t,MidiInputRingBufferSize>& buf,
						MidiEventGenerator& generator,
						MidiEventDispatchUseCase& dispatcher
						):m_ringBuf(buf),m_midiEventGenerator(generator),m_midiEventDispatchUseCase(dispatcher){}

	void MidiEventGeneratUseCase::execute()
	{
		uint8_t midiSignal;

		while (m_ringBuf.dequeue(midiSignal))
		{
			m_midiEventGenerator.inputData(midiSignal);
			if (m_midiEventGenerator.isGeneratcomp())
			{
				EventData eventData;
				eventData = m_midiEventGenerator.createEventGenerat();
				m_midiEventDispatchUseCase.execute(eventData);
			}
		}
	}
}
