#pragma once
#include "IMsgEventSender.hpp"
#include "SharedMsgBufferStorage.hpp"

namespace Infrastructure::Event
{

	// PURPOSE:
	// 共有メモリのメッセージイベントバッファへメッセージIDをセットする
	// WAY:
	// セットされたメッセージIDは受け取り側がポーリングで監視するため本クラスでは通知を実行しない設計とする
	// SCOPE:
	// 共有メモリのメッセージIDのセットのみを実行
	class MsgEventSender:public IMsgEventSender<MsgEventSender>
	{
	public:
		MsgEventSender(SharedMemory::SharedMsgBufferStorage& storage);
		bool msgSendImpl(Domain::Event::MsgEventId& eventid);
	private:
		SharedMemory::SharedMsgBufferStorage&	m_SharedMsgBufferStorage;
	};

}

#include "MsgEventSender_Impl.hpp"
