#pragma once
#include <stdint.h>
namespace Domain::Event
{

	enum class E_MsgEventId : uint16_t
	{
		// ADSRParameterUpdate用
		ADSRAll,
		ADSRAttack,
		ADSRDecay,
		ADSRSustain,
		ADSRSustainReset,
		ADSRRelease,
		Max
	};

	// PURPOSE:
	// メッセージイベントのディスパッチに使用するイベントID
	struct MsgEventId
	{
		E_MsgEventId eventId;
	};

}
