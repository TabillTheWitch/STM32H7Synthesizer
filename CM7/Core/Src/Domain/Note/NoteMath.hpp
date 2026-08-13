#pragma once
#include <cmath>

namespace Domain::Note
{
	// PURPOSE:
	// Key番号を周波数に変換する関数
	inline float NoteKeyToFrequency(int8_t d)
	{
		return 440.0f * pow(2.0f, (d - 69) / 12.0f);
	}
}
