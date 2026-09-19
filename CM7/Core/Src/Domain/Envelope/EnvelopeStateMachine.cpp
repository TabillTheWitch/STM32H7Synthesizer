#include "EnvelopeStateMachine.hpp"
#include "EnvelopeUpdate.hpp"
using namespace Domain::Envelope::UpdateImpl;

namespace Domain::Envelope
{
	EnvelopeStateMachine::EnvelopeStateMachine(){};

	void EnvelopeStateMachine::noteOff(EnvelopeStatePod& envelope)
	{
		if (!isRelease(envelope) && !isReleased(envelope))
		{
			envelope.m_prevStateLevel = envelope.m_currentLevel;
			envelope.m_elapsed = 0.0f;
			envelope.m_state = E_EnvelopeState::Release;
		}
	}

	void EnvelopeStateMachine::reset(EnvelopeStatePod& envelope,E_EnvelopeState state)
	{
		envelope.m_prevStateLevel = envelope.m_currentLevel;
		envelope.m_elapsed = 0.0f;
		envelope.m_state = state;
	}

	__attribute__((section(".itcm"), noinline))
	void EnvelopeStateMachine::update(EnvelopeStatePod& envelope,const ADSRParamPod& adsr, float dt)
	{
		switch (envelope.m_state)
		{
		case E_EnvelopeState::Attack:    updateAttack(envelope, adsr, dt); break;
		case E_EnvelopeState::Decay:     updateDecay(envelope, adsr, dt); break;
		case E_EnvelopeState::Sustain:   updateSustain(envelope, adsr, dt); break;
		case E_EnvelopeState::Sustained: updateSustained(envelope, adsr, dt); break;
		case E_EnvelopeState::Release:   updateRelease(envelope, adsr, dt); break;
		case E_EnvelopeState::Released:  updateReleased(envelope, adsr, dt); break;
		}
	}

	__attribute__((section(".itcm"), noinline))
	bool EnvelopeStateMachine::isReleased(EnvelopeStatePod& envelope) const
	{
		return envelope.m_state == E_EnvelopeState::Released;
	}

	__attribute__((section(".itcm"), noinline))
	bool EnvelopeStateMachine::isRelease(EnvelopeStatePod& envelope) const
	{
		return envelope.m_state == E_EnvelopeState::Release;
	}
}
