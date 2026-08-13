#pragma once
#include <concepts>
#include "MidiEventTypes.hpp"
#include "NoteOnEventPod.hpp"
#include "NoteOffEventPod.hpp"

using namespace Domain::Midi;

// PURPOSE:
// インターフェース提供用のCRTP基底クラス
template <typename Derived>
struct IGenerator
{
	bool isGeneratInit() {return static_cast<Derived*>(this)->isGeneratInitImpl();}
	bool isGeneratComp() {return static_cast<Derived*>(this)->isGeneratCompImpl();}
	bool inputData(uint8_t data) {return static_cast<Derived*>(this)->inputDataImpl(data);}
	EventData createEventGenerat() {return static_cast<Derived*>(this)->createEventGeneratImpl();}
};

// PURPOSE:
// Midiイベントジェネレータの共通インターフェース契約
template <typename T>
concept MidiEventGeneratorConcept =
    std::is_base_of_v<IGenerator<T>, T>;
