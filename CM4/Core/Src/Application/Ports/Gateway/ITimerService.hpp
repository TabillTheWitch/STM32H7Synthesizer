#pragma once
#include <concepts>
#include "stdint.h"

// PURPOSE:
// タイマーイベントをセットするための共通インターフェース契約
template <typename T>
concept TimerServiceConcept = requires(T& x, uint16_t time, typename T::callbackFunc cb)
{
	{ x.setTimerImpl(time, cb) }->std::same_as<bool>;
};

// PURPOSE:
// インターフェース提供用のCRTP基底クラス
template<class Derived>
struct ITimerService
{
	bool setTimer(uint16_t time, auto callback) { return static_cast<Derived*>(this)->setTimerImpl(time, callback); }
	bool stopTimer(uint16_t timeout) { return static_cast<Derived*>(this)->stopTimerImpl(timeout); }

};
