#pragma once
#include <stdint.h>
namespace Presentation::ADSR::DTO
{
	// PURPOSE:
	// UIコントローラー用に使用するASDSのスペック値
	struct ADSRUISpecDTO
	{
		uint8_t attackTimeMaxDigit;
		uint8_t decayTimeMaxDigit;
		uint8_t sustainLevelMaxDigit;
		uint8_t sustainResetTimeMaxDigit;
		uint8_t releaseTimeMaxDigit;
		uint8_t parameterCount;
	};
}
