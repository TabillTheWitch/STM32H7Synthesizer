#pragma once

namespace Domain::ADSR
{
	// PURPOSE:
	// 外部層へ渡す用のADSRパラメータのDTO
	struct ADSRParamDTO
	{
		float attackTime;
		float decayTime;
		float sustainLevel;
		float sustainResetTime;
		float releaseTime;
	};
}
