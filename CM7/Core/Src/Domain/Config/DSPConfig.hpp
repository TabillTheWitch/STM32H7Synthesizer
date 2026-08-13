#pragma once

namespace Domain::Config
{
	inline constexpr uint16_t SamplingFreq = 48000;
	inline constexpr uint16_t MinFreq = 20;
	inline constexpr uint16_t MaxFreq = SamplingFreq / 2;
	inline constexpr float DeltaT = 1.0 / SamplingFreq;
	inline constexpr uint8_t ADSRUpdateCycle = 48;
	inline constexpr float ADSRUpdateDeltaT = DeltaT * ADSRUpdateCycle;
}
