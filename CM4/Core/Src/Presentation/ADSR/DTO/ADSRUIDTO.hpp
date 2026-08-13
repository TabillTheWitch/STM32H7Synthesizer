#pragma once

namespace Presentation::ADSR::DTO
{
	// PURPOSE:
	// UI表示用に使用するADSRパラメータ値
	struct ADSRUIDTO
	{
		uint16_t attackTime;
		uint16_t decayTime;
		uint16_t sustainLevel;
		uint16_t sustainResetTime;
		uint16_t releaseTime;
	};
}
