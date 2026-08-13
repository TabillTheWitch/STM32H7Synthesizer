#include "NoteOffGenerator.hpp"

namespace Domain::Midi::GeneratorImpl
{
	bool NoteOffGenerator::inputDataImpl(uint8_t data)
	{
		if (!inputCheck(data)) return false;

		switch (m_compState)
		{
		case NoteOffGenerator::init:
			m_databuf[0] = data;
			m_compState = NoteOffGenerator::wait1;
			break;
		case NoteOffGenerator::wait1:
			m_databuf[1] = data;
			m_compState = NoteOffGenerator::complete;
			break;
		case NoteOffGenerator::complete:
			m_databuf[2] = data;
			m_compState = NoteOffGenerator::completed;
			break;
		case NoteOffGenerator::completed:
			return false;
			break;
		default:
			break;
		}
		return true;
	}

	bool NoteOffGenerator::inputCheck(uint8_t data)
	{
		if (m_compState == NoteOffGenerator::init)
		{
			if ((data & 0xF0) != NOTEOFF) return false;
		}
		else
		{
			if ((data & 0x80) != 0 && (data & 0xF0) >= 0xF0) return false;
		}
		return true;
	}

	bool NoteOffGenerator::isGeneratCompImpl()
	{
		if (m_compState == NoteOffGenerator::completed) return true;
		return false;
	}

	bool NoteOffGenerator::isGeneratInitImpl()
	{
		if (m_compState == NoteOffGenerator::init) return true;
		return false;
	}

	EventData NoteOffGenerator::createEventGeneratImpl()
	{
		if (!isGeneratComp()) return ErrResult("Err_NoteOffGenerat");
		EventData eventData = Domain::Midi::NoteOffEventPod{static_cast<uint8_t>(m_databuf[0] & 0x0F), m_databuf[1], m_databuf[2]};
		return eventData;
	}
}
