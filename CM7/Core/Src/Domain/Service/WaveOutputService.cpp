#include "WaveOutputService.hpp"
#include "DSPMath.hpp"

namespace Domain::Service
{
	WaveOutputService::WaveOutputService(NoteStatePool& notepool, BandLimitedWaveTables& waveTable, ADSRParamPod& adsr)
					:m_notePool(notepool), m_waveTable(waveTable), m_adsr(adsr)
	{
		isADSRUpdateCounter = 1;
		m_gain = 1.f;
	}

	__attribute__((section(".itcm"), noinline))
	float WaveOutputService::execute()
	{
		float sound = 0.f;
		float totalEnvLevel = 0.f;

		// エンベロープの更新
		if (isADSRUpdateCounter == ADSRUpdateCycle)
		{
			m_notePool.update(m_adsr, ADSRUpdateDeltaT);
			isADSRUpdateCounter = 1;
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
			totalEnvLevel += envLevel;

			sound += m_waveTable.get(
					m_notePool.getPhaseByItNo(itNo),
					m_notePool.getFreqByItNo(itNo),
					m_notePool.getTableIdxByItNo(itNo)) * envLevel;
		}

		float targetGain = (totalEnvLevel > 0.f)
		    ? 1.f / sqrtf(totalEnvLevel)
		    : 1.f;

		m_gain += (targetGain - m_gain) * 0.01f;
		sound *= m_gain;

		return Core::softClip(sound);
	}
}
