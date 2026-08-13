#pragma once

namespace Application::Ports::GateWay::Tags
{
	// PURPOSE:
	// ADSRStorageで取得/更新するパラメータの識別に使用する
	struct ADSRAttack{};
	struct ADSRDecay{};
	struct ADSRSustain{};
	struct ADSRSustainReset{};
	struct ADSRRelease{};
}
