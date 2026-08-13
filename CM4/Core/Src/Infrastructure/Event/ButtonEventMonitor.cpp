#include "ButtonEventMonitor.hpp"

namespace Infrastructure::Event
{
	ButtonEventMonitor::ButtonEventMonitor(Dispatcher& dispatcher,Core::StaticQueue<Domain::Event::ButtonEventId,32>& queue):
		m_dispatcher(dispatcher),
		m_queue(queue)
		{}

	void ButtonEventMonitor::processEvent()
	{
		if(!m_queue.isEmpty())
		{
			Domain::Event::ButtonEventId eventid{};
			m_queue.pop(eventid);
			m_dispatcher.dispatch(eventid);
		}
	}
}
