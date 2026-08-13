#pragma once

#include "ADSRView.hpp"
#include "Shared_Storage.hpp"
#include "SSD1306DisplayDriver.hpp"
#include "SharedMemoryAccessor.hpp"
#include "SharedADSRStorage.hpp"
#include "ADSRPresenter.hpp"
#include "ADSRSpecProvider.hpp"
#include "UpdateADSRUseCase.hpp"
#include "UpdateADSRSpecUseCase.hpp"
#include "ADSRViewController.hpp"
#include "StaticQueue.hpp"
#include "ButtonEventDispatcher.hpp"
#include "ButtonEventMonitor.hpp"
#include "MsgEventSender.hpp"
#include "ButtonDebouncer.hpp"



/**
 * 【責務】
 * - 各クラスのインスタンスを管理
 * - インスタンスの初期化処理
 */
namespace Composition
{

	using ADSRView_t =
	        Presentation::ADSR::View::ADSRView<Infrastructure::SSD1306Driver::SSD1306DisplayDriver>;

	using ADSRPresenter_t =
			Presentation::ADSR::Presenter::ADSRPresenter<Infrastructure::SSD1306Driver::SSD1306DisplayDriver>;

	using MsgEventSender_t =
		Infrastructure::Event::MsgEventSender;

	using UpdateADSRUseCase_t =
			Application::UseCase::UpdateParameter::ADSR::UpdateADSRUseCase<
			Infrastructure::SharedMemory::SharedADSRStorage,
			ADSRPresenter_t,MsgEventSender_t>;

	using ADSRViewController_t =
			Presentation::ADSR::Controller::ADSRViewController<
			Infrastructure::SharedMemory::SharedADSRStorage,
			MsgEventSender_t,
			Infrastructure::SSD1306Driver::SSD1306DisplayDriver>;

	using ADSRSpecProvider_t  =
			Presentation::ADSR::Controller::ADSRSpecProvider<
			Infrastructure::SharedMemory::SharedADSRStorage,
			MsgEventSender_t,
			Infrastructure::SSD1306Driver::SSD1306DisplayDriver>;

	using UpdateADSRSpecUseCase_t =
			Application::UseCase::UpdateParameter::ADSR::UpdateADSRSpecUseCase<ADSRSpecProvider_t>;

	ADSRView_t& GetADSRView();
	ADSRViewController_t& GetADSRViewController();
	Application::Event::ButtonEventDispatcher& GetButtonEventDispatcher();
	Core::StaticQueue<Domain::Event::ButtonEventId,32>& GetEventButtonQueue();
	Infrastructure::SSD1306Driver::SSD1306DisplayDriver& GetDisplayDriver();
	Infrastructure::Event::ButtonEventMonitor& GetButtonEventMonitor();
	Infrastructure::Input::Button::ButtonDebouncer& GetButtonDebouncer();

	void MX_Initialization();

	void CompositInitialization();
}
