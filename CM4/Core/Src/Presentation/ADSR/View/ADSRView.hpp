#pragma once
#include "ADSRLayout.hpp"
#include "ADSRUIDTO.hpp"
#include "IDisplayDriver.hpp"

namespace Presentation::ADSR::View
{
	// PURPOSE:
	// ADSRパラメータ更新画面を表示するクラス
	// HOW:
	// プレゼンターからupdateParamが呼び出されて画面のパラメータ値を更新する
	// プレゼンターからupdateCursorが呼び出されて画面のカーソル位置を更新する
	// ORDER:
	// draw処理を実行する場合は事前にディスプレイドライバーを初期化している必要がある
	template<DisplayDriverConcept DisplayDriver>
	class ADSRView
	{
	public:
		ADSRView(DisplayDriver& displayDriverIF,
				const ADSRLayout::ADSRLayoutPos& layoutpos = ADSRLayoutSSD1306,
				const ADSRLayout::ADSRLayoutLabel& layoutlabel = ADSRLayoutString);
		void drawImpl();
		void updateParam(Presentation::ADSR::DTO::ADSRUIDTO & dto);
		void updateCursor(uint8_t col,uint8_t row);
	private:
		void drawText();
		void drawCursor();
		uint16_t getEditValue();
		void Clear();

		DisplayDriver& m_DisplayDriverIF;
		const ADSRLayout::ADSRLayoutPos& m_layoutPos;
		const ADSRLayout::ADSRLayoutLabel& m_layoutLabel;
		Presentation::ADSR::DTO::ADSRUIDTO m_viewData;
		uint8_t m_CursorColPos;
		uint8_t m_CursorRowPos;
	};
}

#include "ADSRView_impl.hpp"
