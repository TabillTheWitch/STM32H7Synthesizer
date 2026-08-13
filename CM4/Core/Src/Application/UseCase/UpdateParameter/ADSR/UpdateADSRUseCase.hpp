#pragma once
#include "IADSRStorageAccess.hpp"
#include "IOutPortPresenter.hpp"
#include "IMsgEventSender.hpp"
#include "ADSRParamDTO.hpp"
#include "ADSRParam.hpp"
#include "ADSRUpdateTag.hpp"

namespace Application::UseCase::UpdateParameter::ADSR
{
	// PURPOSE:
	//　ADSRパラメータのアップデートを実行するユースケースクラス
	// 実行するユースケース処理は以下の3つ
	// 1.ADSRパラメータストレージのアップデート処理
	// 2.アップデートしたことを別コアに通知する処理
	// 3.更新したADSRパラメータをプレゼンテーション層へ渡す処理
	// SCOPE:
	// スペック情報の更新は実行しない
	template<ADSRStorageAccessConcept StorageAccess,
			 OutPortPresenterConcept<Domain::ADSR::ADSRParamDTO> Presenter,
			 MsgEventSenderConcept MsgSender>
	class UpdateADSRUseCase
	{
	public:
		UpdateADSRUseCase(StorageAccess& storage, Presenter& presenter, MsgSender& msgsender);
		void execute(ADSR::ADSRAttack tag,const float adjustValue);
		void execute(ADSR::ADSRDecay tag,const float adjustValue);
		void execute(ADSR::ADSRSustain tag,const float adjustValue);
		void execute(ADSR::ADSRSustainReset tag,const float adjustValue);
		void execute(ADSR::ADSRRelease tag,const float adjustValue);
		void execute(const Domain::ADSR::ADSRParamDTO &adsrdto);

		Domain::ADSR::ADSRParamDTO m_CacheADSR;
		StorageAccess& m_Storage;
		Presenter& m_Presenter;
		MsgSender& m_MsgSender;
	};
}

#include "UpdateADSRUseCase_Impl.hpp"
