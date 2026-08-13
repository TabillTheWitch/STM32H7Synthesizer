#pragma once
#include <stdint.h>
#include "CountDigit.hpp"
#include "ViewLayout.hpp"

namespace Presentation::ADSR::Controller
{
	template<ADSRStorageAccessConcept StorageAccess,
						 MsgEventSenderConcept MsgSender,
						 DisplayDriverConcept DisplayDriver>
	ADSRSpecProvider<StorageAccess,MsgSender,DisplayDriver>::ADSRSpecProvider(ViewController& viewController) :m_viewController(viewController){}

	template<ADSRStorageAccessConcept StorageAccess,
							 MsgEventSenderConcept MsgSender,
							 DisplayDriverConcept DisplayDriver>
	void ADSRSpecProvider<StorageAccess,MsgSender,DisplayDriver>::provideSpecImpl(const Domain::ADSR::ADSRSpecDTO& dto)
	{
		Presentation::ADSR::DTO::ADSRUISpecDTO uispec
		{
			static_cast<uint8_t>(Core::CountDigit(static_cast<int>(dto.attackTimeMax * Presentation::Common::ViewLayout::kPercentScale))),
			static_cast<uint8_t>(Core::CountDigit(static_cast<int>(dto.decayTimeMax * Presentation::Common::ViewLayout::kPercentScale))),
			static_cast<uint8_t>(Core::CountDigit(static_cast<int>(dto.sustainLevelMax * Presentation::Common::ViewLayout::kPercentScale))),
			static_cast<uint8_t>(Core::CountDigit(static_cast<int>(dto.sustainResetTimeMax * Presentation::Common::ViewLayout::kPercentScale))),
			static_cast<uint8_t>(Core::CountDigit(static_cast<int>(dto.releaseTimeMax * Presentation::Common::ViewLayout::kPercentScale))),
			5
		};
		m_viewController.setSpec(uispec);
	}
}
