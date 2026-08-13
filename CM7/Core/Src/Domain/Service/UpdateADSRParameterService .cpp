#include "UpdateADSRParameterService.hpp"
namespace Domain::Service
{
	UpdateADSRParameterService::UpdateADSRParameterService(ADSRParamPod& adsr)
			:m_adsr(adsr){};

	void UpdateADSRParameterService::execute(const ADSRParam& adsr)
	{
		m_adsr.m_attackTime = adsr.attack();
		m_adsr.m_decayTime = adsr.decay();
		m_adsr.m_sustainLevel = adsr.sustain();
		m_adsr.m_sustainResetTime = adsr.sustainReset();
		m_adsr.m_releaseTime = adsr.release();
	}

	void UpdateADSRParameterService::execute(Tags::ADSRAttack,const float data)
	{
		m_adsr.m_attackTime = data;
	}

	void UpdateADSRParameterService::execute(Tags::ADSRDecay,const float data)
	{
		m_adsr.m_decayTime = data;
	}

	void UpdateADSRParameterService::execute(Tags::ADSRSustain,const float data)
	{
		m_adsr.m_sustainLevel = data;
	}

	void UpdateADSRParameterService::execute(Tags::ADSRSustainReset,const float data)
	{
		m_adsr.m_sustainResetTime = data;
	}

	void UpdateADSRParameterService::execute(Tags::ADSRRelease,const float data)
	{
		m_adsr.m_releaseTime = data;
	}

}
