#include <iterator>
#include <string.h>
namespace Infrastructure::SharedMemory
{
	inline SharedMsgBufferStorage::SharedMsgBufferStorage(SharedMemoryAccessor& accessor): m_Accessor(accessor) {}

	inline bool SharedMsgBufferStorage::sharedMemoryInitialization()
	{
		auto pod = m_Accessor.msgbuf();
		if (!pod) return false;
		memset((void*)pod, 0, sizeof(*pod));
		return true;
	}

	inline bool SharedMsgBufferStorage::load(MsgEventId& eventid)
	{
		auto buf = m_Accessor.msgbuf();
		if (!buf || buf->counter == 0) return false;
		uint32_t head = buf->head;
		eventid.eventId = static_cast<E_MsgEventId>(buf->events[head]);
		buf->head = (head + 1) % std::size(buf->events);
		auto tmp = buf->counter;
		tmp -= 1;
		buf->counter = tmp;
		return true;
	}

	inline bool SharedMsgBufferStorage::store(const MsgEventId& eventid)
	{
		auto buf = m_Accessor.msgbuf();
		if (!buf || buf->counter == std::size(buf->events)) return false;
		uint32_t tail = buf->tail;
		buf->events[tail] = static_cast<uint16_t>(eventid.eventId);
		buf->tail = (tail + 1) % std::size(buf->events);
		auto tmp = buf->counter;
		tmp += 1;
		buf->counter = tmp;
		return true;
	}

	inline uint32_t SharedMsgBufferStorage::getCounter()
	{
		if (!m_Accessor.msgbuf()) return 0;
		return m_Accessor.msgbuf()->counter;
	}

}
