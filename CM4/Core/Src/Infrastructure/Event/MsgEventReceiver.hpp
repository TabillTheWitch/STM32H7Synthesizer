#pragma once
#include "MsgEventDispatcher.hpp"
#include "SharedMsgBufferStorage.hpp"

namespace Infrastructure::Event
{

	// PURPOSE:
	// 共有メモリのメッセージイベントバッファからデータを取り出してアプリケーション層のディスパッチャへ渡す
	// CONSTRAINT:
	// msgRecvは処理コストが高いため割り込みコンテキストから呼んでは行けない
	class MsgEventReceiver
	{
		using Dispatcher = Application::Event::MsgEventDispatcher;
	public:
		MsgEventReceiver(SharedMemory::SharedMsgBufferStorage& storage,Dispatcher& dispatcher);
		bool msgRecv();
	private:
		SharedMemory::SharedMsgBufferStorage&	m_SharedMsgBufferStorage;
		Dispatcher& m_MsgDispatcher;
	};
}

#include "MsgEventReceiver_Impl.hpp"
