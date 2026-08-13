#pragma once
#include <span>
#include <stdint.h>

namespace Infrastructure::I2S
{
	// PURPOSE:
	// AxiSramに配置されたI2Sバッファのアドレスを取得するアクセッサ
	// WAY:
	// DCacheを利用するため書き込み完了後にbufferClean関数を実行する必要がある
	class I2SBufferMemoryAccessor
	{
	public:
		I2SBufferMemoryAccessor(std::span<int16_t> buf);
		inline std::span<int16_t> buffer(){return m_buffer;}
		void bufferClean();
	private:
		std::span<int16_t> m_buffer;
	};
}

#include "I2SBufferMemoryAccessor_Impl.hpp"
