#pragma once
#include "IOutPortSpecProvider.hpp"
#include "ADSRSpecDTO.hpp"
#include "ADSRParam.hpp"

using namespace Application::Ports;

namespace Application::UseCase::UpdateParameter::ADSR
{
	// PURPOSE:
	//　プレゼンテーション層へADSRパラメータのスペック情報を渡すユースケースクラス
	// SCOPE:
	// スペック情報を渡すのみでデータ本体は渡さない
	template<OutPortSpecProviderConcept<Domain::ADSR::ADSRSpecDTO> SpecProvider>
	class UpdateADSRSpecUseCase
	{
	public:
		UpdateADSRSpecUseCase(SpecProvider& specprovider)
			: m_SpecProvider(specprovider) {}

		void execute();

		SpecProvider& m_SpecProvider;
	};
}

#include "UpdateADSRSpecUseCase_Impl.hpp"
