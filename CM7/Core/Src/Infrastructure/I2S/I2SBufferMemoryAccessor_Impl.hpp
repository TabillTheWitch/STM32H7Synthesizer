#pragma once

namespace Infrastructure::I2S
{
	inline I2SBufferMemoryAccessor::I2SBufferMemoryAccessor(std::span<int16_t> buf)
	:m_buffer(buf){}


	inline void I2SBufferMemoryAccessor::bufferClean()
	{
		SCB_CleanDCache_by_Addr(
		            reinterpret_cast<uint32_t*>(m_buffer.data()),
					m_buffer.size_bytes());
	}
}
