#pragma once
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "Span2D.hpp"
#include <array>
#include "IDisplayDriver.hpp"

namespace Infrastructure::SSD1306Driver
{
	// PURPOSE:
	// SSD1306の描画処理クラス
	// CONSTRAINT:
	// コア処理部(ssd1306.c)のssd1306_WriteCommand関数にてHAL_I2C_Mem_Writeが実行されており
	// 描画処理が重い場合にsystem_tickを更新する割り込みが禁止されてしまい内部時間が狂う
	// 内部時間が狂った結果osDelayを実行すると元の処理に戻らないバグが発生する
	// 将来的にはI2CをDMA化する対応をとる
	class SSD1306DisplayDriver :public IDisplayDriver<SSD1306DisplayDriver>
	{
	public:
		static constexpr size_t Rows = 64;
		static constexpr size_t Cols = 128;
		static constexpr size_t PackedCols = Cols / 8;

		SSD1306DisplayDriver();

		void drawStringFontLargeImpl(const char* text, uint16_t col, uint16_t row);

		void drawStringFontMediumImpl(const char* text, uint16_t col, uint16_t row);

		void drawStringFontSmallImpl(const char* text, uint16_t col, uint16_t row);

		void drawBitMapImpl(Core::Span2D<const uint8_t> bmp, uint16_t x, uint16_t y);

		void initImpl();

		void clearImpl();
	private:
		void drawString(const char* text, uint16_t col, uint16_t row, const SSD1306_Font_t fontsize);

		void packBitmap(Core::Span2D<const uint8_t> bmp);

		std::array<uint8_t, Rows* PackedCols> packedBuffer{};

	};
}
