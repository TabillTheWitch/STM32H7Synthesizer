#pragma once
#include <stdint.h>
#include <string>
#include "Span2D.hpp"
#include <array>
#include <cstring>

using namespace infrastructure::Common;
namespace Core
{
	// PURPOSE:
	// ディスプレイ表示用に使用するBitMapクラス
	template <size_t MaxRows, size_t MaxCols>
	class BitMap
	{
	public:
		bool resetSize(size_t row, size_t col)
		{
			if (MaxRows < row || MaxCols < col) return false;
			bitMap.resetSize(storage.data(),row,col);
			return true;
		}
		bool setValue(size_t x,size_t y,uint8_t value)
		{
			if (bitMap.rows <= x || bitMap.cols <= y) return false;
			bitMap(x, y) = value;
			return true;
		}
		bool getValue(size_t x, size_t y, uint8_t& value)
		{
			if (bitMap.rows <= x || bitMap.cols <= y) return false;
			value =  bitMap(x, y);
			return true;
		}
		bool clear()
		{
			storage = {};
			return true;
		}

		Span2D<const uint8_t> getSpan() const
		{
			return Span2D<const uint8_t>(storage.data(), bitMap.rows, bitMap.cols);
		}


		bool setRow(size_t row, std::span<const uint8_t> data)
		{
			if (row >= bitMap.rows) return false;
			if (data.size() < bitMap.cols) return false;

			uint8_t* dst = &storage[row * bitMap.cols];

			memcpy(dst, data.data(), bitMap.cols);

			return true;
		}

		bool setAllValue(Span2D<const uint8_t> bitmap)
		{
			if (bitmap.rows != bitMap.rows) return false;
			if (bitmap.cols != bitMap.cols) return false;

			uint8_t* dst = storage.data();
			const size_t total = bitMap.rows * bitMap.cols;
			memcpy(dst, bitmap.data(), total);

			return true;

		}

		BitMap(size_t row, size_t col) :bitMap(storage.data(), row, col) {}
	private:
		std::array<uint8_t, MaxRows * MaxCols> storage;
		Span2D<uint8_t> bitMap;

	};
}
