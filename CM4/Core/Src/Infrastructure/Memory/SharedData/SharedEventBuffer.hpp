#pragma once
#include "MsgEventId.hpp"
#include <stdint.h>
using namespace Domain::Event;
namespace Infrastructure::Memory::SharedData
{
	// PURPOSE:
	// 共有メモリに配置するメッセージバッファ
	// 各コアのコンパイラ最適化の影響を無くすため単純なPOD構造とする
	// WAY:
	// 共有メモリ上でキャッシュライン破壊を防ぐため、32 バイト境界に align して配置する
	// （デュアルコア環境での DCache 整合性を保つため）
	struct alignas(32) SharedEventBuffer
	{
		volatile uint32_t head;
		volatile uint32_t tail;
		volatile uint32_t counter;
		volatile uint16_t events[32];
	};
}
