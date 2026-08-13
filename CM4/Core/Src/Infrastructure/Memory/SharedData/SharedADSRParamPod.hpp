#pragma once
namespace Infrastructure::Memory::SharedData
{
	// PURPOSE:
	// 共有メモリに配置するADSRパラメータのPOD
	// 各コアのコンパイラ最適化の影響を無くすため単純なPOD構造とする
	// WAY:
	// 共有メモリ上でキャッシュライン破壊を防ぐため、32 バイト境界に align して配置する
	// （デュアルコア環境での DCache 整合性を保つため）
	struct alignas(32) SharedADSRParamPod
	{
		volatile float attackTime;
		volatile float decayTime;
		volatile float sustainLevel;
		volatile float sustainResetTime;
		volatile float releaseTime;
	};
}
