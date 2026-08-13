#pragma once

namespace Domain::ADSR
{
	// PURPOSE:
	// dtcmメモリに配置するADSRパラメータのPod
	// WAY:
	// バイナリサイズ安定化のためPodとしている
	// DSPで頻繁にアクセスされるためdtcmに配置している
	struct ADSRParamPod
	{
		float m_attackTime;
		float m_decayTime;
		float m_sustainLevel;
		float m_sustainResetTime;
		float m_releaseTime;
	};
}
