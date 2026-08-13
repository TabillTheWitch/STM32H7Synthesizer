#pragma once
#include <string>

namespace Presentation::Utility
{
	inline std::string toString(int v)
	{
		char buf[32];
		snprintf(buf, sizeof(buf), "%d", v);
		return std::string(buf);
	}

	inline std::string toString(const char* p)
	{
		return std::string(p);
	}

}
