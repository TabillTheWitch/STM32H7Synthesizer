#pragma once
#include "IOutPortPresenter.hpp"
#include "ADSRParamDTO.hpp"
#include "ADSRUIDTO.hpp"
#include "ADSRView.hpp"

namespace Presentation::ADSR::Presenter
{
	// PURPOSE:
	// ADSRパラメータとカーソル位置情報をビューへ渡すクラス
	// HOW:
	// アプリケーション層からビューへパラメータ情報を渡すために使用される
	// コントローラーからビューへカーソル位置情報を渡すために使用される
	// SCOPE:
	// データをUIコントローラー用のDTOに変換して渡す以外のことはしない
	template<DisplayDriverConcept DisplayDriver>
	class ADSRPresenter:
			public IOutPortPresenter<ADSRPresenter<DisplayDriver>,Domain::ADSR::ADSRParamDTO>
	{
		using ADSRView = Presentation::ADSR::View::ADSRView<DisplayDriver>;
	public:
		ADSRPresenter(ADSRView& view) : m_view(view) {};
		void presentOutPortImpl(const Domain::ADSR::ADSRParamDTO& dto);
		void presentCursor(uint8_t cursorCol,uint8_t cursorRow);
	private:
		ADSRView& m_view;
	};
}
#include "ADSRPresenter_impl.hpp"
