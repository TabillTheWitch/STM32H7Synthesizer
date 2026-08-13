#pragma once

namespace Core
{
	// PURPOSE:
	// 軽量なキュークラス
	// HOW:
	// イベントIDのキューとして使用
	template <typename T, size_t QUEUESIZE>
	class StaticQueue
	{
	public:
		bool push(const T& v)
		{
			if (isFull()) return false;
			buf_[tail_] = v;
			tail_ = (tail_ + 1) % QUEUESIZE;
			return true;
		}

		bool pop(T& out)
		{
			if (isEmpty()) return false;
			out = buf_[head_];
			head_ = (head_ + 1) % QUEUESIZE;
			return true;
		}

		bool isFull() const {
			return ((tail_ + 1) % QUEUESIZE) == head_;
		}

		bool isEmpty() const {
			return head_ == tail_;
		}

		size_t size() const {
			if (tail_ >= head_) return tail_ - head_;
			return QUEUESIZE - (head_ - tail_);
		}

	private:
		T buf_[QUEUESIZE];
		volatile size_t head_ = 0;
		volatile size_t tail_ = 0;
	};
}
