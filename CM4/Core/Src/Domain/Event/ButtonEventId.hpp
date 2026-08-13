#pragma once
#include <stdint.h>

namespace Domain::Event
{

	enum class E_ButtonEventId : uint8_t
	{
    	Up = 0,
    	Down,
    	Left,
    	Right,
    	Max
	};

	// PURPOSE:
	// ボタンイベントのディスパッチに使用するイベントID
	struct ButtonEventId
	{
		E_ButtonEventId eventId;
	};
}
