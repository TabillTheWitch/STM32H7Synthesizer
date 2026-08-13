#pragma once
#include <stdint.h>

namespace Domain::WaveTable
{
	// PURPOSE:
	// BandLimitedWaveTablesを高速参照するためのインデックス
	// HOW:
	// NoteOnイベント生成時に値が算出されてNoteStatePodに集約される
	struct TableIndexCache
	{
		uint16_t low;
		uint16_t high;
		float interp;
	};
}
