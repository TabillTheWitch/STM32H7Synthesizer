#pragma once
#include "IOutPortSpecProvider.hpp"
#include "ADSRUIDTO.hpp"
#include "ADSRUISpecDTO.hpp"
#include "ADSRSpecDTO.hpp"
#include "ADSRViewController.hpp"

namespace Presentation::ADSR::Controller
{
	// PURPOSE:
	// ADSRパラメータのスペック情報をコントローラーへ渡すクラス
	// HOW:
	// アプリケーション層からコントローラーへスペック情報を渡すために使用される
	// SCOPE:
	// データをUIコントローラー用のDTOに変換して渡す以外のことはしない
	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	class ADSRSpecProvider:
			public IOutPortSpecProvider<ADSRSpecProvider<StorageAccess,MsgSender,DisplayDriver>,
			Domain::ADSR::ADSRSpecDTO>
	{
		using ViewController = Controller::ADSRViewController<StorageAccess,MsgSender,DisplayDriver>;
	public:
		ADSRSpecProvider(ViewController& viewController);
		void provideSpecImpl(const Domain::ADSR::ADSRSpecDTO& dto);
	private:
		ViewController& m_viewController;
	};
}
#include "ADSRSpecProvider_Impl.hpp"
