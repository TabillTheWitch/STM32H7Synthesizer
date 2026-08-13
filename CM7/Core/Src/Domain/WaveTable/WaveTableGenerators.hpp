#pragma once
#include "DSPMath.hpp"
#include "WaveTableConfig.hpp"

namespace Domain::WaveTable
{
	// PURPOSE:
	// サイン波形の生成処理関数
	float createSinWave(float freq, uint16_t counter)
	{
		const float angle = (Core::PI * 2) * counter / WaveTableSize;
		return std::sin(angle);
	}
}
