#pragma once
#include "SharedADSRParamPod.hpp"
#include "SharedEventBuffer.hpp"

namespace Infrastructure::Memory
{
	extern volatile SharedData::SharedADSRParamPod shared_Adsr;
	extern volatile SharedData::SharedEventBuffer shared_EventBuffer;
}
