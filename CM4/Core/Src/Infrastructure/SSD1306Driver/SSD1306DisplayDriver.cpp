#include "SSD1306DisplayDriver.hpp"

namespace Infrastructure::SSD1306Driver
{
	SSD1306DisplayDriver::SSD1306DisplayDriver()
	{}

	void SSD1306DisplayDriver::initImpl()
	{
		ssd1306_Init();
	}

	void SSD1306DisplayDriver::clearImpl()
	{
		ssd1306_Fill(Black);
	}

	void SSD1306DisplayDriver::drawStringFontLargeImpl(const char* text, uint16_t col, uint16_t row)
	{
		drawString(text, col, row, Font_11x18);
	}

	void SSD1306DisplayDriver::drawStringFontMediumImpl(const char* text, uint16_t col, uint16_t row)
	{
		drawString(text, col, row, Font_7x10);
	}

	void SSD1306DisplayDriver::drawStringFontSmallImpl(const char* text, uint16_t col, uint16_t row)
	{
		drawString(text, col, row, Font_6x8);
	}

	void SSD1306DisplayDriver::drawBitMapImpl(Core::Span2D<const uint8_t> bmp,uint16_t x, uint16_t y)
	{
		packBitmap(bmp);

		ssd1306_Fill(Black);
		ssd1306_DrawBitmap(x, y,  packedBuffer.data(), bmp.cols, bmp.rows, White);
		ssd1306_UpdateScreen();
	}

	void SSD1306DisplayDriver::drawString(const char* text, uint16_t col, uint16_t row, const SSD1306_Font_t fontsize)
	{
		ssd1306_SetCursor(col, row);
		ssd1306_WriteString(const_cast<char*>(text), fontsize, White);
		ssd1306_UpdateScreen();
	}

	void SSD1306DisplayDriver::packBitmap(Core::Span2D<const uint8_t> bmp)
	{
		const size_t rows = bmp.rows;
		const size_t cols = bmp.cols;

		packedBuffer.fill(0);

		for (size_t r = 0; r < rows; r++)
		{
			for (size_t c = 0; c < cols; c++)
			{
				const size_t byteIndex = (r * PackedCols) + (c / 8);
				const size_t bit = c % 8;

				if (bmp(r,c) > 0)
				{
					packedBuffer[byteIndex] |= (1 << bit);
				}
			}
		}
	}
}
