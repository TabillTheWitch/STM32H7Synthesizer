#pragma once
#include "DmaConfig.hpp"
#include <stdint.h>

using namespace Infrastructure::Config;

namespace Infrastructure::Memory
{
	// PURPOSE:
	// AxiSramメモリに配置するI2Sバッファと受信したMIDI信号を保持する変数
	// WAY:
	// キャッシュライン破壊を防ぐため、32 バイト境界に align して配置する
	// （デュアルコア環境での DCache 整合性を保つため）
	alignas(32) extern int16_t I2S_Buffer[I2SBufferSize];
	alignas(32) extern uint8_t UART_RxByte;
}
