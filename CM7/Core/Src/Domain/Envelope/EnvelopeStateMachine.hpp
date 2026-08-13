#pragma once
#include "ADSRParamPod.hpp"
#include "EnvelopeStatePod.hpp"

using namespace Domain::ADSR;

namespace Domain::Envelope
{
	// PURPOSE:
	// エンベロープの状態遷移を実行するクラス
	// SCOPE:
	// 状態遷移詳細処理はEnvelopeUpdate.hppファイルに集約している
	class EnvelopeStateMachine
	{
	public:
		EnvelopeStateMachine();
		void noteOff(EnvelopeStatePod& envelope);
		void reset(EnvelopeStatePod& envelope,E_EnvelopeState state);
		void update(EnvelopeStatePod& envelope,const ADSRParamPod& adsr, float dt);
	private:
		bool isReleased(EnvelopeStatePod& envelope) const;
		bool isRelease(EnvelopeStatePod& envelope) const;
	};
}
