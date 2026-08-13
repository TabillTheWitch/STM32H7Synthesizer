#pragma once
#include <concepts>
#include <stdint.h>
#include "Span2D.hpp"

// PURPOSE:
// ディスプレイへ文字列とBitMapを出力するための共通インターフェース契約
template <typename T>
concept DisplayDriverConcept = requires(T& t, uint16_t row, uint16_t col,const char* text, Core::Span2D<const uint8_t> bmp,uint16_t x, uint16_t y)
{
	{ t.drawStringFontLargeImpl(text,col, row) }->std::same_as<void>;
	{ t.drawStringFontMediumImpl(text, col, row) }->std::same_as<void>;
	{ t.drawStringFontSmallImpl(text, col, row) }->std::same_as<void>;
	{ t.drawBitMapImpl(bmp, x, y) }->std::same_as<void>;
	{ t.initImpl() }->std::same_as<void>;
	{ t.clearImpl() }->std::same_as<void>;
};

// PURPOSE:
// インターフェース提供用のCRTP基底クラス
template<class Derived>
struct IDisplayDriver
{
	void drawStringFontLarge(const char* text, uint16_t col, uint16_t row) { return static_cast<Derived*>(this)->drawStringFontLargeImpl(text,col,row); }
	void drawStringFontMedium(const char* text, uint16_t col, uint16_t row) { return static_cast<Derived*>(this)->drawStringFontMediumImpl(text,col,row); }
	void drawStringFontSmall(const char* text, uint16_t col, uint16_t row) { return static_cast<Derived*>(this)->drawStringFontSmallImpl(text,col,row); }
	void drawBitMap(Core::Span2D<const uint8_t> bmp, uint16_t x, uint16_t y) { return static_cast<Derived*>(this)->drawBitMapImpl(bmp,x,y); }
	void init(){ return static_cast<Derived*>(this)->initImpl(); }
	void clear(){ return static_cast<Derived*>(this)->clearImpl(); }
};
