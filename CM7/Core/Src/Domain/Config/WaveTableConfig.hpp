#pragma once
namespace Domain::Config
{
	// PURPOSE:
	// 位相方向の分解能
    inline constexpr std::size_t WaveTableSize = 1024;
    // PURPOSE:
    // BandLmitedTableの個数
    inline constexpr std::size_t BandLmitedTableSize = 8;
    // PURPOSE:
    // 周波数方向の分解能
    inline constexpr std::size_t FreqToTableLutSize = 2048;
}
