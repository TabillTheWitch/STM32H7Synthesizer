#include "stm32h7xx_hal.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

namespace Infrastructure::Input::Button
{
	// PURPOSE:
	// ボタンのチャタリング対策用のデバウンスクラス
	// HOW:
	// 割り込み側では notifyPress() により押下タイミングを記録するだけにする
	// 実際のデバウンス解除はタスク側の updateDebounce() で行う
	// CONSTRAINT:
	// updateDebounce()はxTaskGetTickCountを実行するためタスク以外では使用しない
	class ButtonDebouncer
	{
	public:
		ButtonDebouncer();
		bool isDebounced();
		void notifyPress();
		void updateDebounce();
	private:
		volatile uint32_t m_lastPressedTime = 0;
		static const uint32_t waittime = 100;
		volatile bool pendingPress = false;
	};
}
