#pragma once
#include <concepts>
#include <span>

// PURPOSE:
// インターフェース提供用のCRTP基底クラス
template <typename Derived>
struct IAudioBufferAccess
{
	void commitFrame() {return static_cast<Derived*>(this)->commitFrameImpl();}
	std::span<int16_t> acquireWritableFrame() {return static_cast<Derived*>(this)->acquireWritableFrameImpl();}
};

// PURPOSE:
// オーディオ出力用バッファの共通インターフェース契約
// acquireWritableFrameは書き込み可能なバッファを返す処理
// commitFrameは書き込み完了を確定する処理
template <typename T>
concept AudioBufferAccessConcept =
    std::is_base_of_v<IAudioBufferAccess<T>, T>;
