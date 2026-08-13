#pragma once
#include <stdint.h>
namespace Presentation::Common
{
	// PURPOSE:
	// パラメータ更新画面の共通レイアウト情報
	struct ViewLayout
	{
		static constexpr float kPercentScale = 100.0f;

		struct CursorLayoutPos
		{
			uint8_t CursorColStartPosX;
			uint8_t CursorColPosXInterval;
			uint8_t CursorColPosY;
			uint8_t CursorRowPosX;
			uint8_t CursorRowStartPosY;
			uint8_t CursorRowPosYInterval;
		};

		struct CursorLayoutLabel
		{
			const char* CursorColLabel;
			const char* CursorRowLabel;
		};

		struct EditLayoutPos
		{
			uint8_t editLavelStartX;
			uint8_t editLavelXInterval;
			uint8_t editLavelStartY;
		};
	};
}

// PURPOSE:
// パラメータ更新画面の共通カーソルレイアウト配置定義(SSD1306用)
using namespace Presentation::Common;
constexpr ViewLayout::CursorLayoutPos CursorLayoutSSD1306 = {
	.CursorColStartPosX = 121,
	.CursorColPosXInterval = 7,
	.CursorColPosY = 10,
	.CursorRowPosX = 0,
	.CursorRowStartPosY = 10,
	.CursorRowPosYInterval = 8,
};

// PURPOSE:
// パラメータ更新画面の共通カーソル表示定義
constexpr ViewLayout::CursorLayoutLabel CursorLayoutString =
{
	.CursorColLabel = "^",
	.CursorRowLabel = ">"
};

// PURPOSE:
// パラメータ更新画面の編集値の共通表示位置(SSD306用)
constexpr ViewLayout::EditLayoutPos EditLayoutSSD1306 =
{
	.editLavelStartX = 121,
	.editLavelXInterval = 7,
	.editLavelStartY = 0
};
