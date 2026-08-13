
namespace Application::Event
{
	inline void ButtonEventDispatcher::dispatch(Domain::Event::ButtonEventId e)
	{
		m_buttonHandlers[static_cast<size_t>(e.eventId)]();
	}

	inline void ButtonEventDispatcher::registHandler(Domain::Event::ButtonEventId e,Handler handler)
	{
		m_buttonHandlers[static_cast<size_t>(e.eventId)] = handler;
	}
}
