#pragma once
#include "ITimerService.hpp"
#include "Delegate.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

namespace infrastructure
{
	// PURPOSE:
	// クラス関数をタイマーイベントとして登録し実行するクラス
	// HOW:
	// setTimerImplにてクラス関数をタイマーハンドラとして登録
	// timerCallbackStaticを経由して登録したクラス関数が実行される
	// CONSTRAINT:
	// 負荷の高い関数をタイマーハンドラとして登録してはいけない
	// (タイムアウトが発生し処理が停止するため）
	class TimerService :public ITimerService<TimerService>
	{
    public:
        using callbackFunc = Core::Delegate<void>;

        TimerService();

        bool setTimerImpl(uint16_t time, callbackFunc callback);

        bool stopTimerImpl(uint16_t timeout);

    private:
        TimerHandle_t timerHandle{};
        callbackFunc callback;

        static void timerCallbackStatic(TimerHandle_t xTimer)
        {
            auto* self = static_cast<TimerService*>(pvTimerGetTimerID(xTimer));
            self->timerCallback();
        }

        void timerCallback();

	};
}
