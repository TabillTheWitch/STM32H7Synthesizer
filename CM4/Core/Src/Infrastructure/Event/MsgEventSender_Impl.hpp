

namespace Infrastructure::Event
{
	inline MsgEventSender::MsgEventSender(SharedMemory::SharedMsgBufferStorage& storage):m_SharedMsgBufferStorage(storage)
	{};

	inline bool MsgEventSender::msgSendImpl(Domain::Event::MsgEventId& eventid)
	{
		if(!m_SharedMsgBufferStorage.store(eventid)) return false;
		return true;
	}

}
