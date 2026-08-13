#pragma once
#include <stdint.h>
#include <variant>
#include <string>
#include "NoteOnEventPod.hpp"
#include "NoteOffEventPod.hpp"

namespace Domain::Midi
{
	typedef std::string ErrResult;
	// PURPOSE:
	// Midiイベントジェネレータから生成されるデータの型エイリアス
	using EventData = std::variant<std::monostate,NoteOnEventPod, NoteOffEventPod, ErrResult>;
	inline constexpr uint8_t NOTEON = 0x90;
	inline constexpr uint8_t NOTEOFF = 0x80;
}
