#pragma once
#include <span>

namespace Core
{
	// PURPOSE:
	// 2次元配列版のspanクラス
	template <typename T>
	struct Span2D
	{
		size_t rows;
		size_t cols;

		std::span<T> data;

		Span2D(T* ptr, size_t r, size_t c)
			:rows(r), cols(c), data(ptr, r* c) {
		}

		Span2D(){};

		void resetSize(T* ptr, size_t r, size_t c)
		{
			cols = c;
			data(ptr, r * c);
		}

		T& operator()(size_t r, size_t c)
		{
			return data[r * cols + c];
		}
	};
}
