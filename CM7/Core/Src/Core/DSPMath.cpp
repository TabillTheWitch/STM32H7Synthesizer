#include "DSPMath.hpp"

namespace Core
{
    __attribute__((section(".itcm"), noinline))
	float softClip(float x)
	{
		return x / (1.0f + fabsf(x));
	}
}
