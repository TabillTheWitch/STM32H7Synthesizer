#include <string>
#include "ToString.h"
#include "CountDigit.hpp"

namespace Presentation::ADSR::View
{

	template<DisplayDriverConcept DisplayDriver>
	ADSRView<DisplayDriver>::ADSRView(DisplayDriver& displayDriverIF,
			const ADSRLayout::ADSRLayoutPos& layoutpos,
			const ADSRLayout::ADSRLayoutLabel& layoutlabel)
		:m_DisplayDriverIF(displayDriverIF), m_layoutPos(layoutpos), m_layoutLabel(layoutlabel)
	{
		m_CursorRowPos = 0;
		m_CursorColPos = 0;
		m_viewData.attackTime = 0;
		m_viewData.decayTime = 0;
		m_viewData.sustainLevel = 0;
		m_viewData.sustainResetTime = 0;
		m_viewData.releaseTime = 0;
		Clear();
	}

	template<DisplayDriverConcept DisplayDriver>
	void ADSRView<DisplayDriver>::drawImpl()
	{
		Clear();
		drawText();
		drawCursor();
	}

	template<DisplayDriverConcept DisplayDriver>
	void ADSRView<DisplayDriver>::updateParam(Presentation::ADSR::DTO::ADSRUIDTO & dto)
	{
		m_viewData = dto;
		drawImpl();
	}

	template<DisplayDriverConcept DisplayDriver>
	void ADSRView<DisplayDriver>::updateCursor(uint8_t col,uint8_t row)
	{
		m_CursorColPos = col;
		m_CursorRowPos = row;
		drawImpl();
	}

	template<DisplayDriverConcept DisplayDriver>
	void ADSRView<DisplayDriver>::drawText()
	{
		std::string titleStr = Utility::toString(m_layoutLabel.adsrTitleLabel);
		std::string attackStr = Utility::toString(m_layoutLabel.attackTimeLabel) + ":" + Utility::toString(static_cast<int>(m_viewData.attackTime));;
		std::string decayStr = Utility::toString(m_layoutLabel.decayTimeLabel) + ":" + Utility::toString(static_cast<int>(m_viewData.decayTime));
		std::string sustainStr = Utility::toString(m_layoutLabel.sustainLevelLabel) + ":" + Utility::toString(static_cast<int>(m_viewData.sustainLevel));
		std::string sustainResetStr = Utility::toString(m_layoutLabel.sustainResetTimeLabel) + ":" + Utility::toString(static_cast<int>(m_viewData.sustainResetTime));
		std::string releaseStr = Utility::toString(m_layoutLabel.releaseTimeLabel) + ":" + Utility::toString(static_cast<int>(m_viewData.releaseTime));

		m_DisplayDriverIF.drawStringFontMediumImpl
		(titleStr.c_str(), m_layoutPos.titleLabelX, m_layoutPos.titleLabelY);
		m_DisplayDriverIF.drawStringFontSmall
		(attackStr.c_str(), m_layoutPos.attackLabelX, m_layoutPos.attackLabelY);
		m_DisplayDriverIF.drawStringFontSmall
		(decayStr.c_str(), m_layoutPos.decayLabelX, m_layoutPos.decayLabelY);
		m_DisplayDriverIF.drawStringFontSmall
		(sustainStr.c_str(), m_layoutPos.sustainLabelX, m_layoutPos.sustainLabelY);
		m_DisplayDriverIF.drawStringFontSmall
		(sustainResetStr.c_str(), m_layoutPos.sustainResetLabelX, m_layoutPos.sustainResetLabelY);
		m_DisplayDriverIF.drawStringFontSmall
		(releaseStr.c_str(), m_layoutPos.releaseResetLabelX, m_layoutPos.releaseResetLabelY);

		if(m_CursorRowPos == 0) return;
		uint8_t intervalX = m_layoutPos.edit.editLavelXInterval * (Core::CountDigit(static_cast<int>(getEditValue())) - 1);
		uint8_t editLevelX = m_layoutPos.edit.editLavelStartX - intervalX;
		std::string editStr = Utility::toString(static_cast<int>(getEditValue()));
		m_DisplayDriverIF.drawStringFontMediumImpl
		(editStr.c_str(),editLevelX,m_layoutPos.edit.editLavelStartY);

	}

	template<DisplayDriverConcept DisplayDriver>
	void ADSRView<DisplayDriver>::drawCursor()
	{
		if (m_CursorRowPos == 0) return;
		uint8_t curssorRowPosY = m_layoutPos.cursor.CursorRowStartPosY + m_layoutPos.cursor.CursorRowPosYInterval * (m_CursorRowPos - 1);
		std::string cursorRowStr = Utility::toString(m_layoutLabel.cursorLabel.CursorRowLabel);
		m_DisplayDriverIF.drawStringFontSmall
		(cursorRowStr.c_str(), m_layoutPos.cursor.CursorRowPosX, curssorRowPosY);

		if(m_CursorColPos == 0) return;
		uint8_t curssorColPosX = m_layoutPos.cursor.CursorColStartPosX - m_layoutPos.cursor.CursorColPosXInterval * (m_CursorColPos - 1);
		std::string cursorColStr = Utility::toString(m_layoutLabel.cursorLabel.CursorColLabel);
		m_DisplayDriverIF.drawStringFontMediumImpl
		(cursorColStr.c_str(), curssorColPosX, m_layoutPos.cursor.CursorColPosY);
	}

	template<DisplayDriverConcept DisplayDriver>
	uint16_t ADSRView<DisplayDriver>::getEditValue()
	{
		if(m_CursorRowPos == ADSRLayout::attackRowNo) return m_viewData.attackTime;
		if(m_CursorRowPos == ADSRLayout::decayRowNo) return m_viewData.decayTime;
		if(m_CursorRowPos == ADSRLayout::sustainRowNo) return m_viewData.sustainLevel;
		if(m_CursorRowPos == ADSRLayout::sustainResetRowNo) return m_viewData.sustainResetTime;
		if(m_CursorRowPos == ADSRLayout::releaseRowNo) return m_viewData.releaseTime;

		return 0;
	}

	template<DisplayDriverConcept DisplayDriver>
	void ADSRView<DisplayDriver>::Clear()
	{
		m_DisplayDriverIF.clearImpl();
	}

}
