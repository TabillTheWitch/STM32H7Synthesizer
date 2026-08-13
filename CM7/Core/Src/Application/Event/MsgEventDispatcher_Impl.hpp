
namespace Application::Event
{
	inline void MsgEventDispatcher::dispatch(Domain::Event::MsgEventId e)
	{
		m_msgHandlers[static_cast<size_t>(e.eventId)]();
	}

	inline void MsgEventDispatcher::registHandler(Domain::Event::MsgEventId e,Handler handler)
	{
		m_msgHandlers[static_cast<size_t>(e.eventId)] = handler;
	}
}
