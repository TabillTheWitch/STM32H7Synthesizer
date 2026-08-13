#pragma once
#include "ADSRParamPod.hpp"
#include "ADSRParam.hpp"
#include "ADSRGateWayTag.hpp"

using namespace Domain::ADSR;
using namespace::Application::Ports::GateWay;
namespace Domain::Service
{
	// PURPOSE:
	// エンベロープ状態遷移で使用するADSRパラメータを更新するサービスクラス
	// WAY:
	// サービスクラスためサービスに関わるもの以外は実態を持たない
	class UpdateADSRParameterService
	{
	public:
		UpdateADSRParameterService(ADSRParamPod& adsr);
		void execute(const ADSRParam& adsr);
		void execute(Tags::ADSRAttack,const float data);
		void execute(Tags::ADSRDecay,const float data);
		void execute(Tags::ADSRSustain,const float data);
		void execute(Tags::ADSRSustainReset,const float data);
		void execute(Tags::ADSRRelease,const float data);
	private:
		ADSRParamPod& m_adsr;
	};
}
