#pragma once
#include <stdint.h>

namespace Domain::Midi
{
	// PURPOSE:
	// NoteOffジェネレータが生成するノートイベント
	struct NoteOffEventPod
	{
		uint8_t m_channel;
		uint8_t m_noteKey;
		uint8_t m_velocity;
	};
}
