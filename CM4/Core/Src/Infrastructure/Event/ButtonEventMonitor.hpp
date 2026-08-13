#pragma once
#include "StaticQueue.hpp"
#include "ButtonEventDispatcher.hpp"

namespace Infrastructure::Event
{

	// PURPOSE:
	// ボタンイベントキューからデータを取り出してアプリケーション層のディスパッチャへ渡す
	// CONSTRAINT:
	// ProcessEventは処理コストが高いため割り込みコンテキストから呼んでは行けない
	class ButtonEventMonitor
	{
		using Dispatcher = Application::Event::ButtonEventDispatcher;
	public:
		ButtonEventMonitor(Dispatcher& dispatcher,Core::StaticQueue<Domain::Event::ButtonEventId,32>& queue);

		void processEvent();

	private:
		Dispatcher& m_dispatcher;
		Core::StaticQueue<Domain::Event::ButtonEventId,32>& m_queue;
	};
}
