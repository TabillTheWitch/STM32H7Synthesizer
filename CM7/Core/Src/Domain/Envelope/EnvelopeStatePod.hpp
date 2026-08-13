#pragma once
#include <stdint.h>

namespace Domain::Envelope
{
	enum class E_EnvelopeState : uint8_t
	{
		Attack, Decay, Sustain, Sustained, Release, Released
	};

	// PURPOSE:
	// dtcmメモリに配置するエンベロープ状態のPod
	// WAY:
	// バイナリサイズ安定化のためPodとしている
	// DSPで頻繁にアクセスされるためdtcmに配置している
	// HOW:
	// NoteStatePodクラスに集約され、ノート毎のエンベロープ状態として使用する
	struct EnvelopeStatePod
	{
		E_EnvelopeState m_state = E_EnvelopeState::Attack;
		float m_elapsed = 0;
		float m_currentLevel = 0;
		float m_prevStateLevel = 0;
	};
}
