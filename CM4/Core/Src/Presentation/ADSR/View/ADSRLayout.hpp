#pragma once
#include "ViewLayout.hpp"
#include <stdint.h>

namespace Presentation::ADSR::View
{

	struct ADSRLayout
	{
		// PURPOSE:
		// ADSRパラメータ更新画面のレイアウト配置位置情報
		struct ADSRLayoutPos
		{
			uint8_t bitmapX;
			uint8_t bitmapY;
			uint8_t titleLabelX;
			uint8_t titleLabelY;
			uint8_t attackLabelX;
			uint8_t attackLabelY;
			uint8_t decayLabelX;
			uint8_t decayLabelY;
			uint8_t sustainLabelX;
			uint8_t sustainLabelY;
			uint8_t sustainResetLabelX;
			uint8_t sustainResetLabelY;
			uint8_t releaseResetLabelX;
			uint8_t releaseResetLabelY;
			ViewLayout::EditLayoutPos edit;
			ViewLayout::CursorLayoutPos cursor;
		};

		// PURPOSE:
		// ADSRパラメータ更新画面の表示ラベル情報
		struct ADSRLayoutLabel
		{
			const char* adsrTitleLabel;
			const char* attackTimeLabel;
			const char* decayTimeLabel;
			const char* sustainLevelLabel;
			const char* sustainResetTimeLabel;
			const char* releaseTimeLabel;
			ViewLayout::CursorLayoutLabel cursorLabel;
		};

		// PURPOSE:
		// ADSRパラメータ更新画面で表示するパラメータの行情報
		static constexpr uint8_t attackRowNo = 1;
		static constexpr uint8_t decayRowNo = 2;
		static constexpr uint8_t sustainRowNo = 3;
		static constexpr uint8_t sustainResetRowNo = 4;
		static constexpr uint8_t releaseRowNo = 5;
	};
}

// PURPOSE:
// ADSRパラメータ更新画面のレイアウト配置定義(SSD1306用)
using namespace Presentation::ADSR::View;
constexpr ADSRLayout::ADSRLayoutPos ADSRLayoutSSD1306 = {
	.bitmapX = 64,
	.bitmapY = 60,
	.titleLabelX = 6,
	.titleLabelY = 0,
	.attackLabelX = 6,
	.attackLabelY = 10,
	.decayLabelX = 6,
	.decayLabelY = 18,
	.sustainLabelX = 6,
	.sustainLabelY = 26,
	.sustainResetLabelX = 6,
	.sustainResetLabelY = 34,
	.releaseResetLabelX = 6,
	.releaseResetLabelY = 42,
	.edit = EditLayoutSSD1306,
	.cursor = CursorLayoutSSD1306
};

// PURPOSE:
// ADSRパラメータ更新画面の表示ラベル定義
constexpr ADSRLayout::ADSRLayoutLabel ADSRLayoutString =
{
	.adsrTitleLabel = "ADSR",
	.attackTimeLabel = "AttackTime",
	.decayTimeLabel = "DecayTime",
	.sustainLevelLabel = "SustainLevel",
	.sustainResetTimeLabel = "SustainResetTime",
	.releaseTimeLabel = "ReleaseTime",
	.cursorLabel = CursorLayoutString
};


