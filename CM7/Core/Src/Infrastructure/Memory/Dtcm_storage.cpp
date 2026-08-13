#include "Dtcm_storage.hpp"

namespace Infrastructure::Memory
{
	__attribute__((section(".dtcm_data")))
	Domain::Note::NoteStatePod dtcm_NoteStatePods[Domain::Config::MAX_POLY];
	__attribute__((section(".dtcm_data")))
	bool dtcm_blNoteActive[Domain::Config::MAX_POLY];

	using waveTablePod = std::array<float, Domain::Config::WaveTableSize>;
	__attribute__((section(".dtcm_data")))
	std::array<waveTablePod, Domain::Config::BandLmitedTableSize> dtcm_waveTablePods;

	__attribute__((section(".dtcm_data")))
	Domain::ADSR::ADSRParamPod dtcm_ADSRParamPod;

}
