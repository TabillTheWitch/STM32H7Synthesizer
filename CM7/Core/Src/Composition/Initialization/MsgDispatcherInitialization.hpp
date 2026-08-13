#pragma once
#include "MsgEventDispatcher.hpp"
#include "UpdateADSRUseCase.hpp"

namespace Composition::Initialization::MsgDispatcherInitialization
{
	template<ADSRStorageAccessConcept Storage>
	using MsgHandler =  Application::UseCase::UpdateParameter::UpdateADSRUseCase<Storage>;
	using Dispatcher = Application::Event::MsgEventDispatcher;

	// PURPOSE:
	// 起動時にメッセージイベントのハンドラをディスパッチャに登録するための関数
	template<ADSRStorageAccessConcept Storage>
	void init(Dispatcher &dispatcher,MsgHandler<Storage> &handler)
	{
		Dispatcher::Handler delegate;
		Domain::Event::MsgEventId eventid;

		// 全更新受信時のイベント登録
		delegate =Dispatcher::Handler::bind<MsgHandler<Storage>,&MsgHandler<Storage>::onMsgUpdateADSR>(&handler);
		eventid.eventId = Domain::Event::E_MsgEventId::ADSRAll;
		dispatcher.registHandler(eventid, delegate);

		// Attack更新受信時のイベント登録
		delegate = Dispatcher::Handler::bind<MsgHandler<Storage>,&MsgHandler<Storage>::onMsgUpdateADSRAttack>(&handler);
		eventid.eventId = Domain::Event::E_MsgEventId::ADSRAttack;
		dispatcher.registHandler(eventid, delegate);

		// Decay更新受信時のイベント登録
		delegate = Dispatcher::Handler::bind<MsgHandler<Storage>,&MsgHandler<Storage>::onMsgUpdateADSRDecay>(&handler);
		eventid.eventId = Domain::Event::E_MsgEventId::ADSRDecay;
		dispatcher.registHandler(eventid, delegate);

		// Sustain更新受信時のイベント登録
		delegate = Dispatcher::Handler::bind<MsgHandler<Storage>,&MsgHandler<Storage>::onMsgUpdateADSRSustain>(&handler);
		eventid.eventId = Domain::Event::E_MsgEventId::ADSRSustain;
		dispatcher.registHandler(eventid, delegate);

		// SustainReset更新受信時のイベント登録
		delegate = Dispatcher::Handler::bind<MsgHandler<Storage>,&MsgHandler<Storage>::onMsgUpdateADSRSustainReset>(&handler);
		eventid.eventId = Domain::Event::E_MsgEventId::ADSRSustainReset;
		dispatcher.registHandler(eventid, delegate);

		// Release更新受信時のイベント登録
		delegate = Dispatcher::Handler::bind<MsgHandler<Storage>,&MsgHandler<Storage>::onMsgUpdateADSRRelease>(&handler);
		eventid.eventId = Domain::Event::E_MsgEventId::ADSRRelease;
		dispatcher.registHandler(eventid, delegate);

	}
}
