#pragma once

namespace Domain::ADSR
{
	// PURPOSE:
	// 外部層へ渡す用のADSRパラメータのスペックDTO
	struct ADSRSpecDTO
	{
		float attackTimeMax;
		float decayTimeMax;
		float sustainLevelMax;
		float sustainResetTimeMax;
		float releaseTimeMax;
	};
}
