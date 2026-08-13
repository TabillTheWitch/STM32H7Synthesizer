#include "stm32h7xx_hal.h"
#include "CompositionRoot.hpp"

extern "C"
{
	// PURPOSE:
	// I2S転送時のコールバック関数
	//　I2SDmaBufferStorageの書き込み位置の切り替えを実行する
	// CONSTRAINT:
	// 割り込み処理のため書き込み位置の切り替え以外は実行してはいけない
	// SCOPE:
	// I2Sバッファの書き込み位置の切り替えのみ実行
	volatile bool test;
	void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hsai)
	{
		auto& audioOutBuffer = Composition::GetAudioOutBuffer();
		audioOutBuffer.onHalfTransfer();
	}

	void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hsai)
	{
		auto& audioOutBuffer = Composition::GetAudioOutBuffer();
		audioOutBuffer.onFullTransfer();
	}
}
