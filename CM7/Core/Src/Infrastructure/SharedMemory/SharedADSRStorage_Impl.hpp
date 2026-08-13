#include <string.h>
namespace Infrastructure::SharedMemory
{

	inline bool SharedADSRStorage::loadImpl(ADSRParam& param)
	{
		const auto* pod = m_Accessor.adsr();
		if (!pod) return false;
		param = ADSRParam{
				pod->attackTime,
				pod->decayTime,
				pod->sustainLevel,
				pod->sustainResetTime,
				pod->releaseTime};
		return true;
	}

	inline bool SharedADSRStorage::sharedMemoryInitialization()
	{
		auto* pod = m_Accessor.adsr();
		if (!pod) return false;
		memset((void*)pod, 0, sizeof(*pod));
		return true;
	}

	inline bool SharedADSRStorage::loadFieldImpl(Tags::ADSRAttack,float& data)
	{
		auto* pod = m_Accessor.adsr();
				if (!pod) return false;
				data = pod->attackTime;
				return true;
	}

	inline bool SharedADSRStorage::loadFieldImpl(Tags::ADSRDecay,float& data)
	{
		auto* pod = m_Accessor.adsr();
				if (!pod) return false;
				data = pod->decayTime;
				return true;
	}

	inline bool SharedADSRStorage::loadFieldImpl(Tags::ADSRSustain,float& data)
	{
		auto* pod = m_Accessor.adsr();
				if (!pod) return false;
				data = pod->sustainLevel;
				return true;
	}

	inline bool SharedADSRStorage::loadFieldImpl(Tags::ADSRSustainReset,float& data)
	{
		auto* pod = m_Accessor.adsr();
				if (!pod) return false;
				data = pod->sustainResetTime;
				return true;
	}

	inline bool SharedADSRStorage::loadFieldImpl(Tags::ADSRRelease,float& data)
	{
		auto* pod = m_Accessor.adsr();
				if (!pod) return false;
				data = pod->releaseTime;
				return true;
	}

	inline bool SharedADSRStorage::storeImpl(const ADSRParam& param)
	{
		auto* pod = m_Accessor.adsr();
		if (!pod) return false;
		pod->attackTime = param.attack();
		pod->decayTime = param.decay();
		pod->sustainLevel = param.sustain();
		pod->sustainResetTime = param.sustainReset();
		pod->releaseTime = param.release();
		return true;
	}
	inline bool SharedADSRStorage::updateFieldImpl(Tags::ADSRAttack,const float data)
	{
		auto* pod = m_Accessor.adsr();
		if (!pod) return false;
		pod->attackTime = data;
		return true;
	}

	inline bool SharedADSRStorage::updateFieldImpl(Tags::ADSRDecay,const float data)
	{
		auto* pod = m_Accessor.adsr();
		if (!pod) return false;
		pod->decayTime = data;
		return true;
	}

	inline bool SharedADSRStorage::updateFieldImpl(Tags::ADSRSustain,const float data)
	{
		auto* pod = m_Accessor.adsr();
		if (!pod) return false;
		pod->sustainLevel = data;
		return true;
	}

	inline bool SharedADSRStorage::updateFieldImpl(Tags::ADSRSustainReset,const float data)
	{
		auto* pod = m_Accessor.adsr();
		if (!pod) return false;
		pod->sustainResetTime = data;
		return true;
	}

	inline bool SharedADSRStorage::updateFieldImpl(Tags::ADSRRelease,const float data)
	{
		auto* pod = m_Accessor.adsr();
		if (!pod) return false;
		pod->releaseTime = data;
		return true;
	}

}
