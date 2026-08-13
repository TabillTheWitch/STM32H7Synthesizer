#pragma once
#include "WaveOutputService.hpp"
#include "IAudioBufferAccess.hpp"
#include <span>

using namespace Domain;

namespace Application::UseCase::Audio
{
	// PURPOSE:
	// 生成したオーディオ波形をオーディオバッファに書き込むユースケースクラス
	// HOW:
	// DSPループタスクにて本クラスのexecuteを繰り返し実行する
	// CONSTRAINT:
	// 処理負荷が高いため割り込みコンテキストで実行しては行けない
	// ORDER:
	// 事前にm_AudioBufferAccessの初期化が完了している必要がある
	template<AudioBufferAccessConcept AudioBufferAccess>
	class AudioOutUseCase
	{
	public:
		AudioOutUseCase(Service::WaveOutputService& service,AudioBufferAccess& access);
		void execute();
	private:
		Service::WaveOutputService& m_WaveOutputService;
		AudioBufferAccess& m_AudioBufferAccess;
		//uint16_t test;
	};
}

#include "AudioOutUseCase_Impl.hpp"
