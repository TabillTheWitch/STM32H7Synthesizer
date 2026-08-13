#include "ADSRGateWayTag.hpp"

namespace Application::UseCase::UpdateParameter
{
	template<ADSRStorageAccessConcept Storage>
	UpdateADSRUseCase<Storage>::UpdateADSRUseCase(Storage& storage,Domain::Service::UpdateADSRParameterService& updateService)
	:m_adsrStorage(storage),m_updateService(updateService){}

	template<ADSRStorageAccessConcept Storage>
	void UpdateADSRUseCase<Storage>::onMsgUpdateADSR()
	{
		m_adsrStorage.load(m_adsr);
		m_updateService.execute(m_adsr);
	}

	template<ADSRStorageAccessConcept Storage>
	void UpdateADSRUseCase<Storage>::onMsgUpdateADSRAttack()
	{
		float data = 0;
		Application::Ports::GateWay::Tags::ADSRAttack tag{};
		m_adsrStorage.loadField(tag,data);
		m_adsr.setAttack(data);
		m_updateService.execute(tag,m_adsr.attack());
	}

	template<ADSRStorageAccessConcept Storage>
	void UpdateADSRUseCase<Storage>::onMsgUpdateADSRDecay()
	{
		float data = 0;
		Application::Ports::GateWay::Tags::ADSRDecay tag{};
		m_adsrStorage.loadField(tag,data);
		m_adsr.setDecay(data);
		m_updateService.execute(tag,m_adsr.decay());
	}

	template<ADSRStorageAccessConcept Storage>
	void UpdateADSRUseCase<Storage>::onMsgUpdateADSRSustain()
	{
		float data = 0;
		Application::Ports::GateWay::Tags::ADSRSustain tag{};
		m_adsrStorage.loadField(tag,data);
		m_adsr.setSustain(data);
		m_updateService.execute(tag,m_adsr.sustain());
	}

	template<ADSRStorageAccessConcept Storage>
	void UpdateADSRUseCase<Storage>::onMsgUpdateADSRSustainReset()
	{
		float data = 0;
		Application::Ports::GateWay::Tags::ADSRSustainReset tag{};
		m_adsrStorage.loadField(tag,data);
		m_adsr.setSustainReset(data);
		m_updateService.execute(tag,m_adsr.sustainReset());
	}

	template<ADSRStorageAccessConcept Storage>
	void UpdateADSRUseCase<Storage>::onMsgUpdateADSRRelease()
	{
		float data = 0;
		Application::Ports::GateWay::Tags::ADSRRelease tag{};
		m_adsrStorage.loadField(tag,data);
		m_adsr.setRelease(data);
		m_updateService.execute(tag,m_adsr.release());
	}
}
