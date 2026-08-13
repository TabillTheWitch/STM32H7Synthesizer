#pragma once
#include "EnvelopeStatePod.hpp"
#include "TableIndexCache.hpp"

using namespace Domain::Envelope;

namespace Domain::Note
{
	// PURPOSE:
	// dtcmメモリに配置するNote状態のPod
	// WAY:
	// バイナリサイズ安定化のためPodとしている
	// DSPで頻繁にアクセスされるためdtcmに配置している
	// HOW:
	// NoteStatePoolクラスにてNoteStateでラップしたNoteStatePodが最大発音数分集約される
	struct NoteStatePod
	{
		uint8_t m_channel = 0;
		uint8_t m_noteKey = 0;
		float m_velocity = 1.f;
		float m_phase = 0.f;
		float m_freq = 0.f;
		WaveTable::TableIndexCache m_tableIdxCache;
		EnvelopeStatePod m_envelope;
	};
}
