#pragma once
#include "IADSRStorageAccess.hpp"
#include "ADSRParam.hpp"
#include "UpdateADSRParameterService.hpp"

namespace Application::UseCase::UpdateParameter
{
	// PURPOSE:
	// ストレージのADSRパラメータ更新結果をDSP用ADSRパラメータに反映するユースケースクラス
	// HOW:
	// ストレージ更新後にMsgEventDispatcherからonMsgUpdateADSR等が呼ばれる
	// ORDER:
	// ストレージは事前に初期化されている必要がある
	template<ADSRStorageAccessConcept Storage>
	class UpdateADSRUseCase
	{
	public:
		UpdateADSRUseCase(Storage& storage,Domain::Service::UpdateADSRParameterService& updateService);
		void onMsgUpdateADSR();
		void onMsgUpdateADSRAttack();
		void onMsgUpdateADSRDecay();
		void onMsgUpdateADSRSustain();
		void onMsgUpdateADSRSustainReset();
		void onMsgUpdateADSRRelease();
	private:
		Domain::ADSR::ADSRParam m_adsr;
		Storage& m_adsrStorage;
		Domain::Service::UpdateADSRParameterService& m_updateService;
	};
}

#include "UpdateADSRUseCase_Impl.hpp"
