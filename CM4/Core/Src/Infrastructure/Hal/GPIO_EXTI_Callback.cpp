#include "GPIO_EXTI_Callback.hpp"
#include "main.h"

// PURPOSE:
// ボタン押下検知時の割り込みコールバック関数
//　ボタンイベントキューへイベントIDをセットする
// CONSTRAINT:
// 割り込み処理のため軽量キューへのイベントpushのみを実行
// イベント処理の実行はタスク側で行う
// SCOPE:
// ボタンイベントIDのキューセットのみを実行
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	using namespace Presentation;
	using namespace Infrastructure;
	Infrastructure::Input::Button::ButtonDebouncer& buttonDebouncer = Composition::GetButtonDebouncer();

	if (buttonDebouncer.isDebounced()) return;
	buttonDebouncer.notifyPress();

	Core::StaticQueue<Domain::Event::ButtonEventId,32>& queue = Composition::GetEventButtonQueue();
    if (GPIO_Pin == GPIO_PIN_8)
    {
    	Domain::Event::ButtonEventId eventid{Domain::Event::E_ButtonEventId::Up};
    	queue.push(eventid);
    }
    else if(GPIO_Pin == GPIO_PIN_9)
    {
    	Domain::Event::ButtonEventId eventid{Domain::Event::E_ButtonEventId::Down};
    	queue.push(eventid);
    }
    else if(GPIO_Pin == GPIO_PIN_10)
	{
    	Domain::Event::ButtonEventId eventid{Domain::Event::E_ButtonEventId::Left};
    	queue.push(eventid);
	}
    else if(GPIO_Pin == GPIO_PIN_12)
	{
    	Domain::Event::ButtonEventId eventid{Domain::Event::E_ButtonEventId::Right};
    	queue.push(eventid);
	}

}
