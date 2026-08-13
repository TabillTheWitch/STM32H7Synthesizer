#include <string.h>
namespace Application::UseCase::UpdateParameter::ADSR
{
	template<ADSRStorageAccessConcept StorageAccess,
					 OutPortPresenterConcept<Domain::ADSR::ADSRParamDTO> Presenter,
					 MsgEventSenderConcept MsgSender>
	UpdateADSRUseCase<StorageAccess,Presenter,MsgSender>::UpdateADSRUseCase(StorageAccess& storage, Presenter& presenter, MsgSender& msgsender)
				: m_Storage(storage), m_Presenter(presenter),m_MsgSender(msgsender)
	{
		//
		memset((void*)&m_CacheADSR, 0, sizeof(m_CacheADSR));
	}


	template<ADSRStorageAccessConcept StorageAccess,
				 OutPortPresenterConcept<Domain::ADSR::ADSRParamDTO> Presenter,
				 MsgEventSenderConcept MsgSender>
	void UpdateADSRUseCase<StorageAccess,Presenter,MsgSender>::execute(ADSR::ADSRAttack tag,const float adjustValue)
	{
		if(!ADSRParam::isInRange(m_CacheADSR.attackTime + adjustValue)) return;
		// 共有メモリ更新
		m_CacheADSR.attackTime = m_CacheADSR.attackTime + adjustValue;
		m_Storage.updateField(Tags::ADSRAttack{}, m_CacheADSR.attackTime);
		// コア間通知
		MsgEventId eventid{E_MsgEventId::ADSRAttack};
		if(!m_MsgSender.msgSend(eventid)) return;
		// プレゼンター呼び出し
		m_Presenter.presentOutPort(m_CacheADSR);
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 OutPortPresenterConcept<Domain::ADSR::ADSRParamDTO> Presenter,
					 MsgEventSenderConcept MsgSender>
	void UpdateADSRUseCase<StorageAccess,Presenter,MsgSender>::execute(ADSR::ADSRDecay tag,const float adjustValue)
	{
		if(!ADSRParam::isInRange(m_CacheADSR.decayTime + adjustValue)) return;
		// 共有メモリ更新
		m_CacheADSR.decayTime = m_CacheADSR.decayTime + adjustValue;
		m_Storage.updateField(Tags::ADSRDecay{}, m_CacheADSR.decayTime);
		// コア間通知
		MsgEventId eventid{E_MsgEventId::ADSRDecay};
		if(!m_MsgSender.msgSend(eventid)) return;
		// プレゼンター呼び出し
		m_Presenter.presentOutPort(m_CacheADSR);
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 OutPortPresenterConcept<Domain::ADSR::ADSRParamDTO> Presenter,
					 MsgEventSenderConcept MsgSender>
	void UpdateADSRUseCase<StorageAccess,Presenter,MsgSender>::execute(ADSR::ADSRSustain tag,const float adjustValue)
	{
		if(!ADSRParam::isInRange(m_CacheADSR.sustainLevel + adjustValue)) return;
		// 共有メモリ更新
		m_CacheADSR.sustainLevel = m_CacheADSR.sustainLevel + adjustValue;
		m_Storage.updateField(Tags::ADSRSustain{}, m_CacheADSR.sustainLevel);
		// コア間通知
		MsgEventId eventid{E_MsgEventId::ADSRSustain};
		if(!m_MsgSender.msgSend(eventid)) return;
		// プレゼンター呼び出し
		m_Presenter.presentOutPort(m_CacheADSR);
	}

	template<ADSRStorageAccessConcept StorageAccess,
						 OutPortPresenterConcept<Domain::ADSR::ADSRParamDTO> Presenter,
						 MsgEventSenderConcept MsgSender>
	void UpdateADSRUseCase<StorageAccess,Presenter,MsgSender>::execute(ADSR::ADSRSustainReset tag,const float adjustValue)
	{
		if(!ADSRParam::isInRange(m_CacheADSR.sustainResetTime + adjustValue)) return;
		// 共有メモリ更新
		m_CacheADSR.sustainResetTime = m_CacheADSR.sustainResetTime + adjustValue;
		m_Storage.updateField(Tags::ADSRSustainReset{}, m_CacheADSR.sustainResetTime);
		// コア間通知
		MsgEventId eventid{E_MsgEventId::ADSRSustainReset};
		if(!m_MsgSender.msgSend(eventid)) return;
		// プレゼンター呼び出し
		m_Presenter.presentOutPort(m_CacheADSR);
	}

	template<ADSRStorageAccessConcept StorageAccess,
							 OutPortPresenterConcept<Domain::ADSR::ADSRParamDTO> Presenter,
							 MsgEventSenderConcept MsgSender>
	void UpdateADSRUseCase<StorageAccess,Presenter,MsgSender>::execute(ADSR::ADSRRelease tag,const float adjustValue)
	{
		if(!ADSRParam::isInRange(m_CacheADSR.releaseTime + adjustValue)) return;
		// 共有メモリ更新
		m_CacheADSR.releaseTime = m_CacheADSR.releaseTime + adjustValue;
		m_Storage.updateField(Tags::ADSRRelease{}, m_CacheADSR.releaseTime);
		// コア間通知
		MsgEventId eventid{E_MsgEventId::ADSRRelease};
		if(!m_MsgSender.msgSend(eventid)) return;
		// プレゼンター呼び出し
		m_Presenter.presentOutPort(m_CacheADSR);
	}

	template<ADSRStorageAccessConcept StorageAccess,
								 OutPortPresenterConcept<Domain::ADSR::ADSRParamDTO> Presenter,
								 MsgEventSenderConcept MsgSender>
	void UpdateADSRUseCase<StorageAccess,Presenter,MsgSender>::execute(const Domain::ADSR::ADSRParamDTO &adsrdto)
	{
		ADSRParam adsrvo
		{
			adsrdto.attackTime,
			adsrdto.decayTime,
			adsrdto.sustainLevel,
			adsrdto.sustainResetTime,
			adsrdto.releaseTime
		};
		// 共有メモリ更新
		m_Storage.store(adsrvo);
		// コア間通知
		MsgEventId eventid{E_MsgEventId::ADSRAll};
		if(!m_MsgSender.msgSend(eventid)) return;
		// プレゼンター呼び出し
		m_CacheADSR.attackTime = adsrvo.attack();
		m_CacheADSR.decayTime = adsrvo.decay();
		m_CacheADSR.sustainLevel = adsrvo.sustain();
		m_CacheADSR.sustainResetTime = adsrvo.sustainReset();
		m_CacheADSR.releaseTime = adsrvo.release();
		m_Presenter.presentOutPort(m_CacheADSR);
	}
}
