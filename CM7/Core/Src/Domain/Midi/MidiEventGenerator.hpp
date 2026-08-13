#pragma once
#include <stdint.h>
#include <variant>
#include "IGenerator.hpp"
#include "MidiEventTypes.hpp"
#include "NoteOnGenerator.hpp"
#include "NoteOffGenerator.hpp"

// PURPOSE:
// Midiイベントジェネレータの共通インターフェース契約
template <typename... Ts>
requires(MidiEventGeneratorConcept<Ts> &&...)
using GeneratorVariant = std::variant<Ts...>;

namespace Domain::Midi
{
	// PURPOSE:
	// Midi信号からMidiイベントを生成するクラス
	// WAY:
	// Midiイベント生成の拡張性や可読性を考慮してジェネレータの切り替えはstd::varinatで可能としている
	// イベントが増えた際は以下のvariantにジェネレータを追加する
	// GeneratorVariant<GeneratorImpl::NoteOnGenerator,GeneratorImpl::NoteOffGenerator>
	// HOW:
	// Midi信号をinputData関数に渡してイベントを生成する
	// createEventGenerat関数で生成したイベントを外部に出力する
	class MidiEventGenerator
	{
	public:
		MidiEventGenerator();
		void inputData(uint8_t data);
		bool isGeneratcomp();
		EventData createEventGenerat();
	private:
		GeneratorVariant<GeneratorImpl::NoteOnGenerator,GeneratorImpl::NoteOffGenerator> m_GeneratorImpl;
		void createGenerator(uint8_t data);
		bool isEventData(uint8_t data);
		bool isStateInit();
		uint8_t m_runningData = 0;
	};
}
