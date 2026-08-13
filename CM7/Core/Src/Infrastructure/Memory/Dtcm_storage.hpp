#pragma once
#include "NoteStatePoolConfig.hpp"
#include "NoteStatePod.hpp"
#include "WaveTableConfig.hpp"
#include "ADSRParamPod.hpp"
#include <array>

namespace Infrastructure::Memory
{
	extern Domain::Note::NoteStatePod dtcm_NoteStatePods[Domain::Config::MAX_POLY];
	extern bool dtcm_blNoteActive[Domain::Config::MAX_POLY];

	using waveTablePod = std::array<float, Domain::Config::WaveTableSize>;
	extern std::array<waveTablePod, Domain::Config::BandLmitedTableSize> dtcm_waveTablePods;

	extern Domain::ADSR::ADSRParamPod dtcm_ADSRParamPod;
}
