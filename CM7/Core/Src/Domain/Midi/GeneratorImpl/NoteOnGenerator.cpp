#include "NoteOnGenerator.hpp"

namespace Domain::Midi::GeneratorImpl
{
	bool NoteOnGenerator::inputDataImpl(uint8_t data)
	{

		if(!inputCheck(data)) return false;

		switch (m_compState)
		{
		case NoteOnGenerator::init:
			m_databuf[0] = data;
			m_compState = NoteOnGenerator::wait1;
			break;
		case NoteOnGenerator::wait1:
			m_databuf[1] = data;
			m_compState = NoteOnGenerator::complete;
			break;
		case NoteOnGenerator::complete:
			m_databuf[2] = data;
			m_compState = NoteOnGenerator::completed;
			break;
		case NoteOnGenerator::completed:
			return false;
			break;
		default:
			break;
		}
		return true;
	}

	bool NoteOnGenerator::inputCheck(uint8_t data)
	{
		if (m_compState == NoteOnGenerator::init)
		{
			if ((data & 0xF0) != NOTEON) return false;
		}
		else
		{
			if ((data & 0x80) != 0 && (data & 0xF0) >= 0xF0) return false;
		}
		return true;
	}
	
	bool NoteOnGenerator::isGeneratCompImpl()
	{
		if (m_compState == NoteOnGenerator::completed) return true;
		return false;
	}

	bool NoteOnGenerator::isGeneratInitImpl()
	{
		if (m_compState == NoteOnGenerator::init) return true;
		return false;
	}

	EventData NoteOnGenerator::createEventGeneratImpl()
	{
		if (!isGeneratComp()) return ErrResult("Err_NoteOnGenerat");
		EventData eventData = Domain::Midi::NoteOnEventPod{static_cast<uint8_t>(m_databuf[0] & 0x0F), m_databuf[1], m_databuf[2]};
		return eventData;
	}
}
