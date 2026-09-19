
namespace Application::UseCase::Audio
{
	template<AudioBufferAccessConcept AudioBufferAccess>
	inline AudioOutUseCase<AudioBufferAccess>::AudioOutUseCase(Service::WaveOutputService& service,AudioBufferAccess& access)
		:m_WaveOutputService(service),m_AudioBufferAccess(access){}

	template<AudioBufferAccessConcept AudioBufferAccess>
	inline void AudioOutUseCase<AudioBufferAccess>::execute()
	{
		std::span<int16_t> frame = m_AudioBufferAccess.acquireWritableFrame();
	    if (frame.empty()) {
	        return;
	    }

	    for (size_t i = 0;i < frame.size();i++)
	    {
	    	frame[i] = static_cast<int16_t>(m_WaveOutputService.execute() * 0x7fff);
	    }
	    m_AudioBufferAccess.commitFrame();
	}
}
