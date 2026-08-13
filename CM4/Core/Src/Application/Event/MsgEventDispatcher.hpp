#pragma once
#include "Delegate.hpp"
#include "MsgEventId.hpp"
#include <array>

namespace Application::Event
{
	// PURPOSE:
	// メッセージイベントIDに紐づくハンドラを管理するクラス
	class MsgEventDispatcher
	{
	public:
		using Handler = Core::Delegate<void>;
		void dispatch(Domain::Event::MsgEventId e);
		void registHandler(Domain::Event::MsgEventId e,Handler handler);
	private:

		std::array<Handler, static_cast<size_t>(Domain::Event::E_MsgEventId::Max)> m_msgHandlers;
	};
}

#include "MsgEventDispatcher_Impl.hpp"
