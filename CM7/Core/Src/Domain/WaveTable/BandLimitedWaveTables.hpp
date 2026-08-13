#pragma once
#include <stdint.h>
#include <span>
#include "WaveTable.hpp"
#include "TableIndexCache.hpp"
#include "WaveTableConfig.hpp"
#include "DSPConfig.hpp"

using namespace Domain::Config;

namespace Domain::WaveTable
{
	// PURPOSE:
	// 帯域制限付きウェーブテーブルの実装クラス
	// WAY:
	// WaveTablePodの実態はdtcmに配置されるためポインタとして渡される
	// 渡されたPodからWaveTableクラスを生成しm_waveTablesにセットする
	class BandLimitedWaveTables
	{
	public:
		using waveTablePod = std::array<float, WaveTableSize>;
		BandLimitedWaveTables(std::span<waveTablePod,BandLmitedTableSize> tablepod);
		float get(float phase, float freq, TableIndexCache tableIdx) const;
		TableIndexCache createTableIndexCache(float freq) const;
		void generateWaveTable(WaveTable::WaveGenerateCommand command);
	private:
		std::array<WaveTable,BandLmitedTableSize> m_waveTables;
		std::array<float,BandLmitedTableSize> m_tableFreqs;
		std::array<uint16_t,FreqToTableLutSize> m_indices;

		static constexpr float FreqToIndex = WaveTableSize / (1.0 * MaxFreq);
		static constexpr float MinFreqLog = log2(MinFreq);
		static constexpr float MaxFreqLog = log2(MaxFreq);
	};
}
