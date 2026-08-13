

namespace Infrastructure::SharedMemory
{
	inline volatile SharedADSRParamPod* SharedMemoryAccessor::adsr()
	{
		return m_AdsrShared;
	}

	inline volatile SharedEventBuffer* SharedMemoryAccessor::msgbuf()
	{
		return m_MsgBufShared;
	}

}
