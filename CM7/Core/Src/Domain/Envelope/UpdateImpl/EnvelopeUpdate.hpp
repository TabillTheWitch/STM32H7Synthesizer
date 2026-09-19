#pragma once
#include <algorithm>
#include <cmath>
#include "EnvelopeStatePod.hpp"
#include "ADSRParamPod.hpp"

using namespace Domain::ADSR;

// PURPOSE:
// エンベロープ状態遷移処理の詳細
namespace Domain::Envelope::UpdateImpl
{
	__attribute__((section(".itcm"), noinline))
    void updateAttack(EnvelopeStatePod& envelope, const ADSRParamPod& adsr, float dt)
    {
        if (adsr.m_attackTime <= 0.0f)
        {
        	envelope.m_currentLevel = 1.0f;
        	envelope.m_prevStateLevel = envelope.m_currentLevel;
        	envelope.m_elapsed = 0.0f;
        	envelope.m_state = E_EnvelopeState::Decay;
            return;
        }

        envelope.m_elapsed += dt;
        const float t = std::clamp(envelope.m_elapsed / adsr.m_attackTime, 0.0f, 1.0f);
        envelope.m_currentLevel = std::lerp(envelope.m_prevStateLevel, 1.0f, t);

        if (envelope.m_elapsed >= adsr.m_attackTime)
        {
        	envelope.m_prevStateLevel = envelope.m_currentLevel;
        	envelope.m_elapsed -= adsr.m_attackTime;
        	envelope.m_state = E_EnvelopeState::Decay;
        }
    }

	__attribute__((section(".itcm"), noinline))
	void updateDecay(EnvelopeStatePod& envelope, const ADSRParamPod& adsr, float dt)
    {

        if (adsr.m_decayTime <= 0.0f)
        {
        	envelope.m_currentLevel = adsr.m_sustainLevel;
        	envelope.m_prevStateLevel = envelope.m_currentLevel;
        	envelope.m_elapsed = 0.0f;
        	envelope.m_state = E_EnvelopeState::Sustain;
            return;
        }

        envelope.m_elapsed += dt;
        const float t = std::clamp(envelope.m_elapsed / adsr.m_decayTime, 0.0f, 1.0f);
        envelope.m_currentLevel = std::lerp(envelope.m_prevStateLevel, adsr.m_sustainLevel, t);

        if (envelope.m_elapsed >= adsr.m_decayTime)
        {
        	envelope.m_prevStateLevel = envelope.m_currentLevel;
        	envelope.m_elapsed -= adsr.m_decayTime;
        	envelope.m_state = E_EnvelopeState::Sustain;
        }
    }

	__attribute__((section(".itcm"), noinline))
	void updateSustain(EnvelopeStatePod& envelope, const ADSRParamPod& adsr, float dt)
    {
        if (adsr.m_sustainResetTime <= 0.0f)
        {
        	envelope.m_currentLevel = adsr.m_sustainLevel;
        	envelope.m_prevStateLevel = envelope.m_currentLevel;
        	envelope.m_elapsed = 0.0f;
        	envelope.m_state = E_EnvelopeState::Sustained;
            return;
        }

        envelope.m_elapsed += dt;
        const float t = std::clamp(envelope.m_elapsed / adsr.m_sustainResetTime, 0.0f, 1.0f);
        envelope.m_currentLevel = std::lerp(envelope.m_prevStateLevel, adsr.m_sustainLevel, t);

        if (envelope.m_elapsed >= adsr.m_sustainResetTime)
        {
        	envelope.m_currentLevel = adsr.m_sustainLevel;
        	envelope.m_prevStateLevel = envelope.m_currentLevel;
        	envelope.m_elapsed = 0.0f;
        	envelope.m_state = E_EnvelopeState::Sustained;
        }
    }

	__attribute__((section(".itcm"), noinline))
	void updateSustained(EnvelopeStatePod& , const ADSRParamPod& , float ){}

	__attribute__((section(".itcm"), noinline))
	void updateRelease(EnvelopeStatePod& envelope, const ADSRParamPod& adsr, float dt)
    {
        if (adsr.m_releaseTime <= 0.0f)
        {
        	envelope.m_currentLevel = 0.0f;
        	envelope.m_prevStateLevel = 0.0f;
        	envelope.m_elapsed = 0.0f;
        	envelope.m_state = E_EnvelopeState::Released;
            return;
        }

        envelope.m_elapsed += dt;
        const float t = std::clamp(envelope.m_elapsed / adsr.m_releaseTime, 0.0f, 1.0f);
        envelope.m_currentLevel = std::lerp(envelope.m_prevStateLevel, 0.0f, t);

        if (envelope.m_elapsed >= adsr.m_releaseTime)
        {
        	envelope.m_currentLevel = 0.0f;
        	envelope.m_prevStateLevel = 0.0f;
        	envelope.m_elapsed = 0.0f;
        	envelope.m_state = E_EnvelopeState::Released;
        }
    }

	__attribute__((section(".itcm"), noinline))
	void updateReleased(EnvelopeStatePod& , const ADSRParamPod& , float ){}
}
