#include "WaveTable.hpp"

namespace Domain::WaveTable
{
	WaveTable::WaveTable(std::array<float, WaveTableSize>& table):m_waveTable(&table){m_waveTable->fill(0);};


	__attribute__((section(".itcm"), noinline))
	float WaveTable::get(float phase) const
	{
		float indexFloat = phase * PhaseToIndexScale;
		size_t idx = static_cast<size_t>(indexFloat) & (WaveTableSize - 1);
		size_t next = (idx + 1) & (WaveTableSize - 1);
		float t = indexFloat - static_cast<float>(idx);
		return std::lerp((*m_waveTable)[idx],(*m_waveTable)[next],t);
	}

	void WaveTable::generateWaveTable(float freq,WaveGenerateCommand command)
	{
		float maxAbs = 0.f;

		for (uint16_t i = 0; i < WaveTableSize; ++i)
		{
			float v = command(freq, i);
			(*m_waveTable)[i] = v;
			maxAbs = std::max(maxAbs, std::fabs(v));
		}

		// 正規化（±1.0 に収める）
		if (maxAbs > 0.0f)
		{
			for (uint16_t i = 0; i < WaveTableSize; ++i)
			{
				(*m_waveTable)[i] /= maxAbs;
			}
		}

	}
}
