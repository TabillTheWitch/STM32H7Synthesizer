

namespace Infrastructure::I2S
{
	inline I2SDmaBufferStorage::I2SDmaBufferStorage(I2S_HandleTypeDef* hsai_tx,I2SBufferMemoryAccessor& accessor)
			:m_hsai(hsai_tx),m_BufferAccessor(accessor){}


	inline void I2SDmaBufferStorage::start()
	{
		m_BufferAccessor.bufferClean();
		HAL_I2S_Transmit_DMA(m_hsai,
							 reinterpret_cast<uint16_t*>(m_BufferAccessor.buffer().data()),
							 I2SBufferSize);
	}

	inline void I2SDmaBufferStorage::stop()
	{
		HAL_I2S_DMAStop(m_hsai);
	}

	inline std::span<int16_t> I2SDmaBufferStorage::acquireWritableFrameImpl()
	{
		if (!m_writableReady) {
			return {};
		}

		m_writableReady = false;
		std::span<int16_t> buffer = m_BufferAccessor.buffer();

	    if (m_phase == Phase::Half)
	    {
	        // 前半だけ返す
	        return std::span<int16_t>(buffer.data(), buffer.size()/2);
	    }
	    else
	    {
	        // 後半だけ返す
	        return std::span<int16_t>(buffer.data() + buffer.size()/2,buffer.size()/2);
	    }
	}

	inline void I2SDmaBufferStorage::commitFrameImpl()
	{
		m_BufferAccessor.bufferClean();
	}

	// --- HAL コールバックから呼ばれる ---
	inline void I2SDmaBufferStorage::onHalfTransfer()
	{
		updateWritableBuffer(Phase::Half);
	}

	inline void I2SDmaBufferStorage::onFullTransfer()
	{
		updateWritableBuffer(Phase::Full);
	}

	inline void I2SDmaBufferStorage::updateWritableBuffer(Phase phase)
	{
		if (phase == Phase::Half)
		{
			m_phase = phase;
		}
		else
		{
			m_phase = phase;
		}
		m_writableReady = true;
	}

}

