#include "NoteStatePool.hpp"

namespace Domain::Pool
{
	NoteStatePool::NoteStatePool(std::span<bool, Config::MAX_POLY> noteIsActive,std::span<NoteStatePod, Config::MAX_POLY> notepod)
	{
		for(std::size_t i = 0; i < Config::MAX_POLY; i++)
		{
			noteIsActive[i] = false;
			m_slots[i] = Slot{&noteIsActive[i],NoteState(notepod[i])};
		}
	}

	void NoteStatePool::createNoteState(NoteOnEventPod noteon,WaveTable::TableIndexCache tableIdx)
	{
		for (Slot& slot : m_slots)
		{
			if (!*slot.active)
			{
				*slot.active = true;
				slot.note.initialize(noteon, tableIdx);
				return;
			}
		}
	}

	__attribute__((section(".itcm"), noinline))
	void NoteStatePool::update(const ADSRParamPod& adsr, float dt)
	{
		for (Slot& slot : m_slots)
		{
			if (*slot.active && slot.note.isReleased())
			{
				*slot.active = false;
				continue;
			}
			if (*slot.active) slot.note.update(adsr, dt);
		}
	}

	__attribute__((section(".itcm"), noinline))
	void NoteStatePool::noteoff(NoteOffEventPod noteoff)
	{
		for (Slot& slot : m_slots)
		{
			if (!*slot.active) continue;
			if (slot.note.getChannel() == noteoff.m_channel && slot.note.getNoteKey() == noteoff.m_noteKey &&
				!slot.note.isRelease() && !slot.note.isReleased())
			{
				slot.note.noteoff();
				break;
			}
		}
	}

	__attribute__((section(".itcm"), noinline))
	bool NoteStatePool::isActive(uint16_t no) const
	{
		return *m_slots[no].active;
	}

	__attribute__((section(".itcm"), noinline))
	void NoteStatePool::advancePhaseByItNo(uint16_t no,float phaseDelta)
	{
		m_slots[no].note.advancePhase(phaseDelta);
	}

}
