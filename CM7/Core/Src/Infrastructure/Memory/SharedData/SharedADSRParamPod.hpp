#pragma once
namespace Infrastructure::Memory::SharedData
{
	struct alignas(32) SharedADSRParamPod
	{
		volatile float attackTime;
		volatile float decayTime;
		volatile float sustainLevel;
		volatile float sustainResetTime;
		volatile float releaseTime;
	};
}
