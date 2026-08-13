#pragma once
#include "EnvelopeStateMachine.hpp"
#include "ADSRParamPod.hpp"
#include "NoteStatePod.hpp"
#include "NoteOnEventPod.hpp"
#include "TableIndexCache.hpp"

using namespace Domain::ADSR;
using namespace Domain::Envelope;
using namespace Domain::Midi;

namespace Domain::Note
{
	// PURPOSE:
	// Note状態を管理するクラス
	// WAY:
	// NoteStatePodはdtcmに配置されるためポインタとして渡される
	// HOW:
	// NoteOnイベント生成時にNoteStatePoolからinitialize関数が呼び出されてNoteOn状態として初期化する
	// NoteOffイベント生成時にNoteStatePoolからnoteoff関数が呼びされてNoteOff状態にする
	// DSP処理内でNoteStatePoolからadvancePhase関数とupdate関数が呼び出されてフェーズとエンベロープ状態を更新する
	class NoteState
	{
	public:
		NoteState() = default;
		NoteState(NoteStatePod& notestate);
		bool isReleased() const;
		bool isRelease() const;
		void initialize(const NoteOnEventPod noteon,WaveTable::TableIndexCache tableIdx);
		void update(const ADSRParamPod& adsr, float dt);
		void noteoff();
		void advancePhase(float phaseDelta);

		inline float 						getCurrentLevel() const			{ return m_noteState->m_envelope.m_currentLevel;}
		inline float 						getVelocity() const				{ return m_noteState->m_velocity;}
		inline uint8_t 						getChannel() const 				{ return m_noteState->m_channel; }
		inline uint8_t 						getNoteKey() const 				{ return m_noteState->m_noteKey; }
		inline float 						getPhase() const 				{ return m_noteState->m_phase; }
		inline float 						getFreq() const		 			{ return m_noteState->m_freq; }
		inline WaveTable::TableIndexCache 	getTableIdx() const	{ return m_noteState->m_tableIdxCache; }

	private:
		NoteStatePod* m_noteState;
		EnvelopeStateMachine m_envelopeStateMachine;
	};
}
