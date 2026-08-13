#pragma once
#include"IGenerator.hpp"

namespace Domain::Midi::GeneratorImpl
{
	// PURPOSE:
	// NoteOnイベント生成用のジェネレートクラス
	class NoteOnGenerator:public IGenerator<NoteOnGenerator>
	{
	public:
		bool isGeneratCompImpl();
		bool isGeneratInitImpl();
		bool inputDataImpl(uint8_t data);
		EventData createEventGeneratImpl();
	private:
		bool inputCheck(uint8_t data);
		uint8_t m_databuf[3] = {};
		enum E_CompState :uint8_t
		{
			init,
			wait1,
			complete,
			completed
		};
		E_CompState m_compState = E_CompState::init;
	};
}
