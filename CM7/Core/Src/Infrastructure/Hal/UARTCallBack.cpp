#include "stm32h7xx_hal.h"
#include "CompositionRoot.hpp"

extern "C"
{
	// PURPOSE:
	// Midi信号受信時のコールバック関数
	// CONSTRAINT:
	// 割り込み処理のためユースケース処理内ではリングバッファへの信号値セット以外は実行してはいけない
	// SCOPE:
	// 受信したMidi信号を取得しリングバッファにセットする処理を実行
	// 最後に割り込みハンドラを再度設定する
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
		auto& midiSignalUseCase = Composition::GetInputMidiSignalUseCase();
		uint8_t* rxByte = Composition::GetUARTRxByte();
		if (huart->Instance == USART3 && *rxByte != 0xF8)
		{
			midiSignalUseCase.execute(*rxByte);
		}
		HAL_UART_Receive_IT(huart, rxByte, 1); // 次の1バイト受信を再設定
	}
}
