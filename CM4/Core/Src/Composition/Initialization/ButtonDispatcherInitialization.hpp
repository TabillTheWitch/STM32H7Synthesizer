#pragma once
#include "Delegate.hpp"
#include "CompositionRoot.hpp"

using namespace Presentation;

namespace Composition::Initialization::ButtonDispatcherInitialization
{
	// PURPOSE:
	// 起動時に各ボタンのイベントハンドラをディスパッチャに登録するための関数
	using Handler = Core::Delegate<void>;
	void init(Application::Event::ButtonEventDispatcher &dispatcher,Composition::ADSRViewController_t &handler)
	{
		Handler delegate;
		Domain::Event::ButtonEventId eventid{};

		// 上ボタン押下時のイベント登録
		delegate = Handler::bind<Composition::ADSRViewController_t,&Composition::ADSRViewController_t::onUpButton>(&handler);
		eventid.eventId = Domain::Event::E_ButtonEventId::Up;
		dispatcher.registHandler(eventid, delegate);

		// 下ボタン押下時のイベント登録
		delegate = Handler::bind<Composition::ADSRViewController_t,&Composition::ADSRViewController_t::onDownButton>(&handler);
		eventid.eventId = Domain::Event::E_ButtonEventId::Down;
		dispatcher.registHandler(eventid, delegate);

		// 左ボタン押下時のイベント登録
		delegate = Handler::bind<Composition::ADSRViewController_t,&Composition::ADSRViewController_t::onLeftButton>(&handler);
		eventid.eventId = Domain::Event::E_ButtonEventId::Left;
		dispatcher.registHandler(eventid, delegate);

		// 右ボタン押下時のイベント登録
		delegate = Handler::bind<Composition::ADSRViewController_t,&Composition::ADSRViewController_t::onRightButton>(&handler);
		eventid.eventId = Domain::Event::E_ButtonEventId::Right;
		dispatcher.registHandler(eventid, delegate);
	}
}
