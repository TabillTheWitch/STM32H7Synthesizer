
namespace Infrastructure::Event
{
	MsgEventReceiver::MsgEventReceiver(SharedMemory::SharedMsgBufferStorage& storage,Dispatcher& dispatcher)
	:m_SharedMsgBufferStorage(storage),m_MsgDispatcher(dispatcher)
	{}

	bool MsgEventReceiver::msgRecv()
	{
		while(m_SharedMsgBufferStorage.getCounter() > 0)
		{
			Domain::Event::MsgEventId eventid{};
			if(!m_SharedMsgBufferStorage.load(eventid)) return false;
			m_dispatcher.dispatch(eventid);
		}
		return true;
	}
}
