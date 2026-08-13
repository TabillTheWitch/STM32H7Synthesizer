#include "MidiEventGenerator.hpp"
namespace Domain::Midi
{
	MidiEventGenerator::MidiEventGenerator()
	{
		m_GeneratorImpl = GeneratorImpl::NoteOnGenerator();
	}


	void MidiEventGenerator::inputData(uint8_t data)
	{
		if (isEventData(data))
		{
			m_runningData = data;
			createGenerator(data);

			std::visit([&](auto& gen)
			{
			    gen.inputData(data);
			}, m_GeneratorImpl);
		}
		else
		{
			if (isStateInit())
			{
				if (m_runningData != 0)
				{
					std::visit([&](auto& gen)
					{
						gen.inputData(m_runningData);
					}, m_GeneratorImpl);
				}
			}
			std::visit([&](auto& gen)
			{
				gen.inputData(data);
			}, m_GeneratorImpl);
		}
	}

	bool MidiEventGenerator::isEventData(uint8_t data)
	{
		return (data & 0x80);
	}

	bool MidiEventGenerator::isStateInit()
	{
		return
		std::visit([this](auto& gen)
		{
		    return gen.isGeneratInit();
		}, m_GeneratorImpl);
	}

	void MidiEventGenerator::createGenerator(uint8_t data)
	{
		uint8_t upper_half_byte = data & 0xF0;
		switch (upper_half_byte)
		{
		case NOTEON:
			m_GeneratorImpl = GeneratorImpl::NoteOnGenerator();
			break;
		case NOTEOFF:
			m_GeneratorImpl = GeneratorImpl::NoteOffGenerator();
			break;
		default:
			break;
		}
	}

	EventData MidiEventGenerator::createEventGenerat()
	{
		return
		std::visit([this](auto& gen)
		{
			return gen.createEventGenerat();
		}, m_GeneratorImpl);
	}

	bool MidiEventGenerator::isGeneratcomp()
	{
		return
		std::visit([this](auto& gen)
		{
			return gen.isGeneratComp();
		}, m_GeneratorImpl);
	}
}
