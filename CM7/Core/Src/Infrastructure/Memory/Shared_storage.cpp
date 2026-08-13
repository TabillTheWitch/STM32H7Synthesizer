#include "shared_storage.hpp"

namespace Infrastructure::Memory
{
	__attribute__((section(".shared_memory")))
	volatile SharedData::SharedADSRParamPod shared_Adsr;

	__attribute__((section(".shared_memory")))
	volatile SharedData::SharedEventBuffer shared_EventBuffer;
}
