#pragma once
#include "ADSRParamDTO.hpp"
#include "ADSRUpdateTag.hpp"
#include "ADSRPresenter.hpp"
#include "ADSRUISpecDTO.hpp"
#include "E_EditMode.hpp"
#include "UpdateADSRUseCase.hpp"

namespace ADSRTag = Application::UseCase::UpdateParameter::ADSR;
namespace Presentation::ADSR::Controller
{
	// PURPOSE:
	// ボタン押下後にADSR画面更新とADSRパラメータ更新の実行を制御するクラス
	// HOW:
	// ボタン押下後にディスパッチャー(アプリケーション層)からイベントハンドラしてonUpButton等の関数が実行される
	// ORDER:
	// ハンドラ関数実行前にsetSpecでADSRパラメータのスペック情報をセットしている必要がある
	// SCOPE:
	// ADSR画面更新とADSRパラメータ更新を実行するかの判断のみで実際の更新処理はこのクラスでは実行しない
	template<ADSRStorageAccessConcept StorageAccess,
				 MsgEventSenderConcept MsgSender,
				 DisplayDriverConcept DisplayDriver>
	class ADSRViewController
	{
		using Presenter = Presentation::ADSR::Presenter::ADSRPresenter<DisplayDriver>;
		using UpdateUseCase = Application::UseCase::UpdateParameter::ADSR::UpdateADSRUseCase<StorageAccess,Presenter,MsgSender>;

	public:
		ADSRViewController(UpdateUseCase& updateUseCase,Presenter &presenter);
		void onUpButton();
	    void onDownButton();
	    void onLeftButton();
	    void onRightButton();
		void setSpec(const DTO::ADSRUISpecDTO spec);
	private:

		UpdateUseCase& m_UpdateUseCase;
		Presenter& m_Presenter;

		uint8_t m_Row;
		uint8_t m_Col;
		Presentation::Common::E_EditMode m_editmode;
		DTO::ADSRUISpecDTO m_spec;

		void addParameter();
		void subParameter();
		void advanceEditDigit();
	};
}

#include "ADSRViewController_Impl.hpp"
