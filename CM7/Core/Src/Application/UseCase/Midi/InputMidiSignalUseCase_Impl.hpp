
namespace Application::UseCase::Midi
{
	inline bool InputMidiSignalUseCase::execute(uint8_t signal)
	{
		return m_ringBuf.enqueue(signal);
	}
}
