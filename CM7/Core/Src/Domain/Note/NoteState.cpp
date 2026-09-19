#include "NoteState.hpp"
#include "NoteMath.hpp"
#include "DSPMath.hpp"

namespace Domain::Note
{
	NoteState::NoteState(NoteStatePod& notestate):m_noteState(&notestate){}

	__attribute__((section(".itcm"), noinline))
	bool NoteState::isReleased() const
	{

		return (m_noteState->m_envelope.m_state == E_EnvelopeState::Released) ? true:false;
	}

	bool NoteState::isRelease() const
	{
		return (m_noteState->m_envelope.m_state == E_EnvelopeState::Release) ? true:false;
	}

	void NoteState::initialize(NoteOnEventPod noteon,WaveTable::TableIndexCache tableIdx)
	{
		m_noteState->m_channel = noteon.m_channel;
		m_noteState->m_noteKey = noteon.m_noteKey;
		m_noteState->m_velocity = noteon.m_velocity / 127.0f;
		m_noteState->m_freq = NoteKeyToFrequency(noteon.m_noteKey);
		m_noteState->m_tableIdxCache = tableIdx;
		m_noteState->m_envelope.m_state = E_EnvelopeState::Attack;
		m_noteState->m_envelope.m_currentLevel = 0;
		m_noteState->m_envelope.m_elapsed = 0;
		m_noteState->m_envelope.m_prevStateLevel = 0;
	}

	__attribute__((section(".itcm"), noinline))
	void NoteState::update(const ADSRParamPod& adsr, float dt)
	{
		m_envelopeStateMachine.update(m_noteState->m_envelope,adsr, dt);
	}

	void NoteState::noteoff()
	{
		m_envelopeStateMachine.noteOff(m_noteState->m_envelope);
	}

	__attribute__((section(".itcm"), noinline))
	void NoteState::advancePhase(float phaseDelta)
	{
		m_noteState->m_phase += phaseDelta * m_noteState->m_freq * Core::TwoPi;
		if (Core::TwoPi < m_noteState->m_phase)
		{
			m_noteState->m_phase -= Core::TwoPi;
		}
	}


}
