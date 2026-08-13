#pragma once
#include "ADSRParamDTO.hpp"
#include "CompositionRoot.hpp"

namespace Composition::Initialization::ADSRParamInitialization
{
	// PURPOSE:
	// 起動時にADSRパラメータを初期化するために必要な関数
	// ORDER:
	// スペック情報を設定した後にパラメータを更新する
	void init(Composition::UpdateADSRSpecUseCase_t &updatespec,Composition::UpdateADSRUseCase_t &update)
	{
		Domain::ADSR::ADSRParamDTO dto
		{
			0.1,
			0.1,
			0.1,
			0.1,
			0.1
		};

		updatespec.execute();
		update.execute(dto);

	}
}
