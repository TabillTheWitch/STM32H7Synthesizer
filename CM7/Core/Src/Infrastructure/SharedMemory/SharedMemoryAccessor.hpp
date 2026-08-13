#pragma once
#include <cstddef>
#include "SharedADSRParamPod.hpp"
#include "SharedEventBuffer.hpp"
using namespace Infrastructure::Memory::SharedData;

namespace Infrastructure::SharedMemory
{
	// PURPOSE:
	// 共有メモリに配置されたオブジェクトのアドレスを取得するアクセッサ
	// WAY:
	// MPUにて共有メモリはNonCacheableに設定されるため
	// cleanCacheとinvalidateCacheの実装は必要ない
	// SCOPE:
	// キャッシュのクリアは実行しない
	class SharedMemoryAccessor
	{
	public:
		SharedMemoryAccessor(volatile SharedADSRParamPod* adsr,volatile SharedEventBuffer* msgbuf)
			: m_AdsrShared(adsr),m_MsgBufShared(msgbuf){}

		volatile SharedADSRParamPod* adsr();
		volatile SharedEventBuffer* msgbuf();
		// MPUの設定で共有メモリはNonCacheableなので実装はひとまず不要
		void cleanCache(void* ptr,size_t size){};
		void invalidateCache(void* ptr,size_t size){};
	private:
		volatile SharedADSRParamPod* m_AdsrShared;
		volatile SharedEventBuffer* m_MsgBufShared;
		// 必要に応じて共有メモリの情報は増やす
	};
}
#include "SharedMemoryAccessor_Impl.hpp"
