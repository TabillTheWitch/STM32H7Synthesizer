
#include "CountDigit.hpp"
#include "ViewLayout.hpp"

namespace Presentation::ADSR::Presenter
{
	template<DisplayDriverConcept DisplayDriver>
	void ADSRPresenter<DisplayDriver>::presentOutPortImpl(const Domain::ADSR::ADSRParamDTO& dto)
	{
		DTO::ADSRUIDTO uidto
		{
			static_cast<uint16_t>(dto.attackTime * Presentation::Common::ViewLayout::kPercentScale),
			static_cast<uint16_t>(dto.decayTime * Presentation::Common::ViewLayout::kPercentScale),
			static_cast<uint16_t>(dto.sustainLevel * Presentation::Common::ViewLayout::kPercentScale),
			static_cast<uint16_t>(dto.sustainResetTime * Presentation::Common::ViewLayout::kPercentScale),
			static_cast<uint16_t>(dto.releaseTime * Presentation::Common::ViewLayout::kPercentScale)
		};

		m_view.updateParam(uidto);
	}

	template<DisplayDriverConcept DisplayDriver>
	void ADSRPresenter<DisplayDriver>::presentCursor(uint8_t cursorCol,uint8_t cursorRow)
	{
		m_view.updateCursor(cursorCol,cursorRow);
	}
}
