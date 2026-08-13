#pragma once
#include <stdint.h>
#include <cmath>

namespace Core
{
	// PURPOSE:
	// リングバッファ実装
	// Midi信号のバッファとして使用
	template<typename T, size_t Size>
	class RingBuffer
	{
		static_assert((Size & (Size - 1)) == 0, "Size must be power of 2");

	public:
		bool enqueue(const T& in) noexcept {
			const auto next = (m_front + 1) & mask;
			if (next == m_rear) return false; // full
			m_buf[m_front] = in;
			m_front = next;
			return true;
		}

		bool dequeue(T& out) noexcept {
			if (m_front == m_rear) return false; // empty
			out = m_buf[m_rear];
			m_rear = (m_rear + 1) & mask;
			return true;
		}

		bool isEmpty() const noexcept { return m_front == m_rear; }
		bool isFull()  const noexcept { return ((m_front + 1) & mask) == m_rear; }

	private:
		static constexpr size_t mask = Size - 1;
		size_t m_front = 0;
		size_t m_rear  = 0;
		T m_buf[Size];
};
}
