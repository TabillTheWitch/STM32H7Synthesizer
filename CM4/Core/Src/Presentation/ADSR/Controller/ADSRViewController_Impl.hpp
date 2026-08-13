#include "ADSRLayout.hpp"
#include "ViewLayout.hpp"
#include <cmath>
#include <string.h>

namespace Presentation::ADSR::Controller
{
	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::ADSRViewController(UpdateUseCase& updateUseCase,Presenter &presenter)
	:m_UpdateUseCase(updateUseCase),m_Presenter(presenter)
	{
		m_Row = 0;
		m_Col = 0;
		m_editmode = E_EditMode::Select;
		memset((void*)&m_spec, 0, sizeof(m_spec));
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	void ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::onUpButton()
	{
		switch (m_editmode)
		{
		case E_EditMode::Select:
			if(m_Row != 0) m_Row--;
			break;
		case E_EditMode::Edit:
			addParameter();
			break;
		default:
			break;
		}
		m_Presenter.presentCursor(m_Col,m_Row);
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	void ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::onDownButton()
	{
		switch (m_editmode)
		{
		case E_EditMode::Select:
			if(m_Row != m_spec.parameterCount) m_Row++;
			break;
		case E_EditMode::Edit:
			subParameter();
			break;
		default:
			break;
		}
		m_Presenter.presentCursor(m_Col,m_Row);
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	void ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::onLeftButton()
	{
		switch (m_editmode)
		{
		case E_EditMode::Select:
			// 後で画面切り替えの処理とかを記載
			// 他画面追加時に、onButton関連のIFを持ったViewControlerの統括クラスから呼び出されるようにする。
			break;
		case E_EditMode::Edit:
			advanceEditDigit();
			break;
		default:
			break;
		}
		m_Presenter.presentCursor(m_Col,m_Row);
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	void ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::onRightButton()
	{
		switch (m_editmode)
		{
		case E_EditMode::Select:
			if(m_Row != 0)
			{
				m_editmode = E_EditMode::Edit;
				m_Col = 1;
			}
			else
			{
				// 画面切り替えの処理
			}
			break;
		case E_EditMode::Edit:
			if(m_Col != 1) m_Col--;
			break;
		default:
			break;
		}
		m_Presenter.presentCursor(m_Col,m_Row);
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	void ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::setSpec(const DTO::ADSRUISpecDTO spec)
	{
		m_spec = spec;
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	void ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::addParameter()
	{
		float addData = std::pow(10,m_Col) / (ViewLayout::kPercentScale * 10);
		switch (m_Row)
		{
		case Presentation::ADSR::View::ADSRLayout::attackRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRAttack{}, addData);
			break;
		case Presentation::ADSR::View::ADSRLayout::decayRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRDecay{}, addData);
			break;
		case Presentation::ADSR::View::ADSRLayout::sustainRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRSustain{}, addData);
			break;
		case Presentation::ADSR::View::ADSRLayout::sustainResetRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRSustainReset{}, addData);
			break;
		case Presentation::ADSR::View::ADSRLayout::releaseRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRRelease{}, addData);
			break;
		default:
			break;
		}
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	void ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::subParameter()
	{
		float subData = 0 - (std::pow(10,m_Col) / (ViewLayout::kPercentScale * 10));
		switch (m_Row)
		{
		case Presentation::ADSR::View::ADSRLayout::attackRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRAttack{}, subData);
			break;
		case Presentation::ADSR::View::ADSRLayout::decayRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRDecay{}, subData);
			break;
		case Presentation::ADSR::View::ADSRLayout::sustainRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRSustain{}, subData);
			break;
		case Presentation::ADSR::View::ADSRLayout::sustainResetRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRSustainReset{}, subData);
			break;
		case Presentation::ADSR::View::ADSRLayout::releaseRowNo:
			m_UpdateUseCase.execute(ADSRTag::ADSRRelease{}, subData);
			break;
		default:
			break;
		}
	}

	template<ADSRStorageAccessConcept StorageAccess,
					 MsgEventSenderConcept MsgSender,
					 DisplayDriverConcept DisplayDriver>
	void ADSRViewController<StorageAccess,MsgSender,DisplayDriver>::advanceEditDigit()
	{
		auto changeDigit = [&](uint8_t maxDigit)
		{
			if(m_Col != maxDigit)
			{
				m_Col++;
			}
			else
			{
				m_Col = 0;
				m_editmode = E_EditMode::Select;
			}
		};

		switch (m_Row)
		{
		case Presentation::ADSR::View::ADSRLayout::attackRowNo:
			changeDigit(m_spec.attackTimeMaxDigit);
			break;
		case Presentation::ADSR::View::ADSRLayout::decayRowNo:
			changeDigit(m_spec.decayTimeMaxDigit);
			break;
		case Presentation::ADSR::View::ADSRLayout::sustainRowNo:
			changeDigit(m_spec.sustainLevelMaxDigit);
			break;
		case Presentation::ADSR::View::ADSRLayout::sustainResetRowNo:
			changeDigit(m_spec.sustainResetTimeMaxDigit);
			break;
		case Presentation::ADSR::View::ADSRLayout::releaseRowNo:
			changeDigit(m_spec.releaseTimeMaxDigit);
			break;
		default:
			break;
		}
	}

}
