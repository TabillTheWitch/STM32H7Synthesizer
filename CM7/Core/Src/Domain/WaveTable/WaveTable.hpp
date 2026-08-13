#pragma once
#include <array> 
#include <stdint.h>
#include "WaveTableConfig.hpp"
#include "DSPMath.hpp"

using namespace Domain::Config;

namespace Domain::WaveTable
{
	// PURPOSE:
	// WaveTableを管理するクラス
	// WAY:
	// WaveTableの実態はdtcmに配置される
	// WaveTable生成関数の詳細は拡張性を考慮して外部からコマンドとして受けて実行される
	// HOW:
	// BandLimitedWaveTables内で実態が生成され、BandLimitedWaveTablesに集約される
	class WaveTable
	{
	public:
		using WaveGenerateCommand = float(*)(float, uint16_t);
		WaveTable() = default;
		WaveTable(std::array<float, WaveTableSize>& table);
		float get(float phase) const;
		void generateWaveTable(float freq,WaveGenerateCommand command);
	private:
		std::array<float, WaveTableSize>* m_waveTable;
		// PURPOSE:
		// PhaseをWaveTableIndexに変換するためのスケール
		static constexpr float PhaseToIndexScale = WaveTableSize / Core::TwoPi;
	};
}
