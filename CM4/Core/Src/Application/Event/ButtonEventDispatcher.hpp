#pragma once
#include "Delegate.hpp"
#include "ButtonEventId.hpp"
#include <array>

namespace Application::Event
{

	// PURPOSE:
	// ボタンイベントIDに紐づくハンドラを管理するクラス
	class ButtonEventDispatcher
	{
	public:
		using Handler = Core::Delegate<void>;
		void dispatch(Domain::Event::ButtonEventId e);
		void registHandler(Domain::Event::ButtonEventId e,Handler handler);
	private:

		std::array<Handler, static_cast<size_t>(Domain::Event::E_ButtonEventId::Max)> m_buttonHandlers;
	};
}

#include "ButtonEventDispatcher_Impl.hpp"
