
namespace Application::UseCase::UpdateParameter::ADSR
{

	template<OutPortSpecProviderConcept<Domain::ADSR::ADSRSpecDTO> SpecProvider>
	void UpdateADSRSpecUseCase<SpecProvider>::execute()
	{
		Domain::ADSR::ADSRSpecDTO spec
		{
			Domain::ADSR::ADSRParam::paramMax(),
			Domain::ADSR::ADSRParam::paramMax(),
			Domain::ADSR::ADSRParam::paramMax(),
			Domain::ADSR::ADSRParam::paramMax(),
			Domain::ADSR::ADSRParam::paramMax(),
		};
		m_SpecProvider.provideSpecImpl(spec);
	}
}
