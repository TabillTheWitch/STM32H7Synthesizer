#pragma once
#include <stdint.h>

namespace Domain::Midi
{
	// PURPOSE:
	// NoteOnジェネレータが生成するノートイベント
	struct NoteOnEventPod
	{
		uint8_t m_channel;
		uint8_t m_noteKey;
		uint8_t m_velocity;
	};
}
