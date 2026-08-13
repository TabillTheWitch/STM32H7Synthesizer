#include "AxiSram_storage.hpp"

namespace Infrastructure::Memory
{
	__attribute__((section(".AxiSram_memory")))
	alignas(32) int16_t I2S_Buffer[I2SBufferSize];

	__attribute__((section(".AxiSram_memory")))
	alignas(32) uint8_t UART_RxByte;;
}
