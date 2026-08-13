#pragma once

namespace Domain::ADSR
{
	// PURPOSE:
	// ADSRパラメータのドメインクラス
	// WAY:
	// 組み込み向けとして動的生成は避ける意図で不変オブジェクトとしていない
	class ADSRParam
	{
	public:
		ADSRParam()
		{
			m_attackTime = 0.0f;
			m_decayTime = 0.0f;
			m_sustainLevel = 0.0f;
			m_sustainResetTime = 0.0f;
			m_releaseTime = 0.0f;
		}
		ADSRParam(float a, float d, float s, float sr, float r)
			: m_attackTime(a)
			, m_decayTime(d)
			, m_sustainLevel(s)
			, m_sustainResetTime(sr)
			, m_releaseTime(r)
		{
			if (!isValid())
			{
				m_attackTime = clamp(a);
				m_decayTime = clamp(d);
				m_sustainLevel = clamp(s);
				m_sustainResetTime = clamp(sr);
				m_releaseTime = clamp(r);
			}
		}

		ADSRParam(const ADSRParam& other)
		    : m_attackTime(other.m_attackTime)
		    , m_decayTime(other.m_decayTime)
		    , m_sustainLevel(other.m_sustainLevel)
		    , m_sustainResetTime(other.m_sustainResetTime)
		    , m_releaseTime(other.m_releaseTime)
		{
			if (!isValid())
			{
				this->setADSR(other);
			}
		}

		ADSRParam& operator=(const ADSRParam& other)
		{
		    if (this != &other)
		    {
		    	this->setADSR(other);
		    }
		    return *this;
		}

		ADSRParam(const ADSRParam&& other)
			: m_attackTime(other.m_attackTime)
			, m_decayTime(other.m_decayTime)
			, m_sustainLevel(other.m_sustainLevel)
			, m_sustainResetTime(other.m_sustainResetTime)
			, m_releaseTime(other.m_releaseTime)
		{
			if (!isValid())
			{
				this->setADSR(other);
			}
		}

		ADSRParam& operator=(const ADSRParam&& other)
		{
			if (this != &other)
			{
				this->setADSR(other);
			}
			return *this;
		}

		float attack() const { return m_attackTime; }
		float decay() const { return m_decayTime; }
		float sustain() const { return m_sustainLevel; }
		float sustainReset() const { return m_sustainResetTime; }
		float release() const { return m_releaseTime; }

		void setAttack(const float v)
		{
		    m_attackTime = clamp(v);
		}

		void setDecay(const float v)
		{
			m_decayTime = clamp(v);
		}

		void setSustain(const float v)
		{
			m_sustainLevel = clamp(v);
		}

		void setSustainReset(const float v)
		{
			m_sustainResetTime = clamp(v);
		}

		void setRelease(const float v)
		{
			m_releaseTime = clamp(v);
		}

		void setADSR(const ADSRParam& adsr)
		{
			m_attackTime = clamp(adsr.attack());
			m_decayTime = clamp(adsr.decay());
			m_sustainLevel = clamp(adsr.sustain());
			m_sustainResetTime = clamp(adsr.sustainReset());
			m_releaseTime = clamp(adsr.release());
		}

		static constexpr float paramMax() { return 1.0f; }
		static constexpr float paramMin() { return 0.0f; }

		bool isValid() const
		{
			return isInRange(m_attackTime)
				&& isInRange(m_decayTime)
				&& isInRange(m_sustainLevel)
				&& isInRange(m_sustainResetTime)
				&& isInRange(m_releaseTime);
		}

		static bool isInRange(float v)
		{
			return v >= paramMin() && v <= paramMax();
		}

	private:

		static float clamp(float v)
		{
			if (v < paramMin()) return paramMin();
			if (v > paramMax()) return paramMax();
			return v;
		}

		float m_attackTime;
		float m_decayTime;
		float m_sustainLevel;
		float m_sustainResetTime;
		float m_releaseTime;
	};

}
