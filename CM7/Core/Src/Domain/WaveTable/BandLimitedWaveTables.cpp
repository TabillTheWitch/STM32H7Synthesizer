#include "BandLimitedWaveTables.hpp"
#include <algorithm>

namespace Domain::WaveTable
{
	BandLimitedWaveTables::BandLimitedWaveTables(std::span<waveTablePod, BandLmitedTableSize> tablepod)
	{
		for (size_t i = 0; i < BandLmitedTableSize; ++i)
		{
			const float rate = 1.0 * i / BandLmitedTableSize;
			const float freq = pow(2, std::lerp(MinFreqLog, MaxFreqLog, rate));
			m_waveTables[i] = WaveTable(tablepod[i]);
			m_tableFreqs[i] = static_cast<float>(freq);
		}

		for (size_t i = 0; i < FreqToTableLutSize; ++i)
		{
			const float freq = static_cast<float>(i / FreqToIndex);
			const auto nextIt = std::upper_bound(m_tableFreqs.begin(), m_tableFreqs.end(), freq);
			m_indices[i] = static_cast<uint16_t>(nextIt - m_tableFreqs.begin());
		}
	}

	__attribute__((section(".itcm"), noinline))
	float BandLimitedWaveTables::get(float phase, float freq, TableIndexCache tableIdx) const
	{
		return std::lerp(m_waveTables[tableIdx.low].get(phase), m_waveTables[tableIdx.high].get(phase), tableIdx.interp);
	}

	__attribute__((section(".itcm"), noinline))
	TableIndexCache BandLimitedWaveTables::createTableIndexCache(float freq) const
	{
		float f = freq * FreqToIndex;
		int idx = (int)f;

		int maxIndex = (int)FreqToTableLutSize - 2;
		if (maxIndex < 0) maxIndex = 0;

		if (idx < 0) idx = 0;
		else if (idx > maxIndex) idx = maxIndex;

		float rate = f - idx;

		return { m_indices[idx], m_indices[idx + 1], rate };
	}

	void BandLimitedWaveTables::generateWaveTable(WaveTable::WaveGenerateCommand command)
	{
		for (size_t i = 0; i < BandLmitedTableSize; ++i)
		{
			const float rate = 1.0 * i / BandLmitedTableSize;
			const float freq = pow(2, std::lerp(MinFreqLog, MaxFreqLog, rate));
			m_waveTables[i].generateWaveTable(freq,command);
		}
	}
}
