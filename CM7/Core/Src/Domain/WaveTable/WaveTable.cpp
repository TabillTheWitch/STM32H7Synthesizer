#include "WaveTable.hpp"

namespace Domain::WaveTable
{
	WaveTable::WaveTable(std::array<float, WaveTableSize>& table):m_waveTable(&table){m_waveTable->fill(0);};


	__attribute__((section(".itcm"), noinline))
	float WaveTable::get(float phase) const
	{
		auto indexFloat = phase * PhaseToIndexScale;
		auto prevIndex = static_cast<size_t>(indexFloat);
		if (WaveTableSize == prevIndex)
		{
			prevIndex -= WaveTableSize;
			indexFloat -= WaveTableSize;
		}
		auto nextIndex = prevIndex + 1;
		if (WaveTableSize == nextIndex)
		{
			nextIndex = 0;
		}
		const auto x01 = indexFloat - prevIndex;
		return std::lerp((*m_waveTable)[prevIndex], (*m_waveTable)[nextIndex], x01);
	}

	void WaveTable::generateWaveTable(float freq,WaveGenerateCommand command)
	{
		for (uint16_t i = 0; i < WaveTableSize; ++i)
		{
			(*m_waveTable)[i] = command(freq,i);
		}
	}
}
