#include "WaveOutputService.hpp"
#include "DSPMath.hpp"

namespace Domain::Service
{
	WaveOutputService::WaveOutputService(NoteStatePool& notepool, BandLimitedWaveTables& waveTable, ADSRParamPod& adsr)
					:m_notePool(notepool), m_waveTable(waveTable), m_adsr(adsr){isADSRUpdateCounter = 0;}

	__attribute__((section(".itcm"), noinline))
	float WaveOutputService::execute()
	{
		float sound = 0.f;

		// エンベロープの更新
		if (isADSRUpdateCounter == ADSRUpdateCycle)
		{
			m_notePool.update(m_adsr, ADSRUpdateDeltaT);
			isADSRUpdateCounter = 0;
		}
		else
		{
			isADSRUpdateCounter++;
		}

		for (uint16_t itNo = 0; itNo < Domain::Config::MAX_POLY; ++itNo)
		{
			if (!m_notePool.isActive(itNo)) continue;

			m_notePool.advancePhaseByItNo(itNo, DeltaT);

			// WaveTableから音を生成する。
			const float envLevel = m_notePool.getCurrentLevelByItNo(itNo) * m_notePool.getVelocityByItNo(itNo);

			sound += m_waveTable.get(
					m_notePool.getPhaseByItNo(itNo),
					m_notePool.getFreqByItNo(itNo),
					m_notePool.getTableIdxByItNo(itNo)) * envLevel;
		}

		return Core::softClip(sound);
	}
}
