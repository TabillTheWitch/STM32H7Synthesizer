#pragma once
#include "stm32h7xx_hal.h"
#include "IAudioBufferAccess.hpp"
#include "I2SBufferMemoryAccessor.hpp"
#include <span>
#include <stdint.h>
#include "DmaConfig.hpp"

using namespace Infrastructure::Config;

namespace Infrastructure::I2S
{
	// PURPOSE:
	// AxiSramに配置されるI2Sバッファの書き込み位置を取得するクラス
	// WAY:
	// 書き込み開始位置はPhase状態で切り替わる作りとなっており疑似的なダブルバッファとして設計されている
	// HOW:
	// acquireWritableFrameImpl関数にてバッファの書き込み開始位置を返す
	// I2Sの転送完了時のコールバック関数にて以下の関数が呼ばれ書き込み開始位置が更新される
	// onHalfTransfer,onFullTransfer
	// 書き込み完了時にはcommitFrameImpl関数を実行しDCacheをクリーンする必要がある
	class I2SDmaBufferStorage:public IAudioBufferAccess<I2SDmaBufferStorage>
	{
	public:
		I2SDmaBufferStorage(I2S_HandleTypeDef* hsai_tx,I2SBufferMemoryAccessor& accessor);
		void start();
		void stop();

		std::span<int16_t> acquireWritableFrameImpl();

		// HAL コールバックから呼ばれるエントリ
		void onHalfTransfer();
		void onFullTransfer();

		void commitFrameImpl();
	private:
		enum class Phase
		{
			Half,
			Full
		};

		void updateWritableBuffer(Phase phase);
		volatile Phase m_phase;

	private:
		I2S_HandleTypeDef* m_hsai;
		I2SBufferMemoryAccessor& m_BufferAccessor;
		volatile bool m_writableReady = false;
	};
}

#include "I2SDmaBufferStorage_Impl.hpp"
