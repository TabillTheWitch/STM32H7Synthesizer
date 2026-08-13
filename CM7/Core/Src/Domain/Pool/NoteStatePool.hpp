#pragma once
#include <span>
#include "NoteState.hpp"
#include "NoteOnEventPod.hpp"
#include "NoteOffEventPod.hpp"
#include "ADSRParamPod.hpp"
#include "NoteStatePoolConfig.hpp"

using namespace Domain::Note;
using namespace Domain::Midi;
using namespace Domain::ADSR;

namespace Domain::Pool
{
	// PURPOSE:
	// 最大発音数分のNote状態を集約するクラス
	// WAY:
	// NoteStatePodやActive判定用のbool値はdtcmに配置されるためコンストラクタでポインタとして渡される
	// HOW:
	// NoteOnイベント生成時にMidiEventDispatchUseCaseからcreateNoteState関数が呼ばれる
	// NoteOffイベント生成時にMidiEventDispatchUseCaseからnoteoff関数が呼ばれる
	// DSP処理内でadvancePhase関数とupdate関数が呼び出されてNoteStateのフェーズと状態を更新する
	class NoteStatePool
	{
	public:
		NoteStatePool() = delete;
		NoteStatePool(std::span<bool, Config::MAX_POLY> noteIsActive,std::span<NoteStatePod, Config::MAX_POLY> notepod);
		void createNoteState(NoteOnEventPod noteon,WaveTable::TableIndexCache tableIdx);
		void update(const ADSRParamPod& adsr, float dt);
		void noteoff(NoteOffEventPod noteoff);
		void advancePhaseByItNo(uint16_t no,float phaseDelta);


		inline float   getCurrentLevelByItNo(uint16_t no) const						{return m_slots[no].note.getCurrentLevel();}
		inline float   getVelocityByItNo(uint16_t no) const							{return m_slots[no].note.getVelocity();}
		inline uint8_t getChannelByItNo(uint16_t no) const							{return m_slots[no].note.getChannel();}
		inline uint8_t getNoteKeyByItNo(uint16_t no) const							{return m_slots[no].note.getNoteKey();}
		inline float   getPhaseByItNo(uint16_t no) const								{return m_slots[no].note.getPhase();}
		inline float   getFreqByItNo(uint16_t no) const								{return m_slots[no].note.getFreq();}
		inline WaveTable::TableIndexCache getTableIdxByItNo(uint16_t no) const		{return m_slots[no].note.getTableIdx();}

		bool isActive(uint16_t no) const;
	private:
		struct Slot
		{
			bool*     active;
			NoteState note;
		};
		std::array<Slot, Config::MAX_POLY> m_slots;
	};
}
