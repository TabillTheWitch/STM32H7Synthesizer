#pragma once
#include <stdint.h>
namespace Presentation::Common
{
	// PURPOSE:
	// 画面の選択モードの判定用に使用される
	enum class E_EditMode : uint8_t
	{
		Select,
		Edit
	};
}
