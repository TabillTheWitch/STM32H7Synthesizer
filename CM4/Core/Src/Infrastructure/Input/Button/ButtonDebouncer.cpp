#include "ButtonDebouncer.hpp"

namespace Infrastructure::Input::Button
{
	ButtonDebouncer::ButtonDebouncer(){};

	bool ButtonDebouncer::isDebounced()
	{
		return pendingPress;
	}

	void ButtonDebouncer::updateDebounce()
	{
		if (pendingPress)
		{
			uint32_t now = xTaskGetTickCount();
			if (m_lastPressedTime == 0)
			{
				m_lastPressedTime = now;
				return;
			}

			if (m_lastPressedTime + waittime  <= now)
			{
				pendingPress = false;
			}
		}
	}

	void ButtonDebouncer::notifyPress()
	{
		pendingPress = true;
		m_lastPressedTime = 0;
	}
}
