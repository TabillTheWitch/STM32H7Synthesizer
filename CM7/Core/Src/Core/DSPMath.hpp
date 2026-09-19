#pragma once
#include <cmath>

namespace Core
{
    constexpr float PI = 3.141592653589793;
    constexpr float TwoPi = PI * 2;

    // PURPOSE:
	// 2点間の値を線形補間する処理
	// BandLimitedWaveTableのテーブル間の線形補間等に使用する
    template <typename T>
    constexpr float invLerp(T a, T b, T v)
    {
        return static_cast<float>(v - a) / static_cast<float>(b - a);
    }

    // PURPOSE:
	// 音声波形のソフトクリップ処理
    // WAY:
    // itcmに配置するため実装はcppに記載
    // DSP処理内部で呼ばれる関数のためitcmに配置している
    float softClip(float x);


}
