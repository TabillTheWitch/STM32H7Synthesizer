#pragma once
#include "MsgEventId.hpp"
#include "SharedMemoryAccessor.hpp"

namespace Infrastructure::SharedMemory
{
	// PURPOSE:
	// 共有メモリに配置されるメッセージの取得/更新を実行するクラス
	// WAY:
	// sharedMemoryInitializationをコンストラクタから分離する意図は
	// 起動直後に共有メモリの値を参照すると処理が停止するため
	// HOW
	// 共有メモリのCounterでメッセージの取得/追加されたことが判断可能
	// storeされたらCounterをインクリメントしloadされたらCounterをデクリメントする
	//　CONSTRAINT：
	// sharedMemoryInitializationは起動後少なくとも10ms経過した後に実行すること
	class SharedMsgBufferStorage
	{
	public:
		SharedMsgBufferStorage(SharedMemoryAccessor& accessor);
		bool sharedMemoryInitialization();
		bool load(MsgEventId& eventid);
		bool store(const MsgEventId& eventid);
		uint32_t getCounter();

	private:
		SharedMemoryAccessor& m_Accessor;
	};
}

#include "SharedMsgBufferStorage_Impl.hpp"
