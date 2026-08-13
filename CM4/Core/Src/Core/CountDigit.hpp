#pragma once
#include <cmath>
#include <cstdlib>

namespace Core
{
	// PURPOSE:
	// 整数の桁数を返す処理
	inline int CountDigit(int data)
	{
		if (data == 0) return 1;
		return std::log10(std::llabs(data)) + 1;
	}
}
