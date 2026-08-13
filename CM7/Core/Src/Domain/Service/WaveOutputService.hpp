#pragma once
#include "BandLimitedWaveTables.hpp"
#include "WaveTable.hpp"
#include "ADSRParamPod.hpp"
#include "NoteStatePool.hpp"

using namespace Domain::Pool;
using namespace Domain::WaveTable;
using namespace Domain::ADSR;
namespace Domain::Service
{
	// PURPOSE:
	// 波形データを1サンプル出力するサービスクラス
	// WAY:
	// サービスクラスためサービスに関わるもの以外は実態を持たない
	class WaveOutputService
	{
	public:
		WaveOutputService(NoteStatePool& notepool, BandLimitedWaveTables& waveTable, ADSRParamPod& adsr);
		float execute();
	private:
		NoteStatePool& m_notePool;
		BandLimitedWaveTables& m_waveTable;
		ADSRParamPod& m_adsr;
		uint8_t isADSRUpdateCounter;
	};
}
