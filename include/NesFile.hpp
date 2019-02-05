#pragma once

#include <vector>
#include <string>

#include <stdint.h>

#include "commonvalues.hpp"
#include "RomBank.hpp"
#include "VRomBank.hpp"
#include "Trainer.hpp"

class NesFile
{
public:
	enum mirroringType {VERTICAL, HORIZONTAL};
	enum videoEncodingType {PAL, NTSC};

	NesFile(const std::string& file, bool pedanticMode = false);

	void LoadFile(const std::string& file, bool pedanticMode = false);

	intmax_t fileSize() const;
	bool valid() const;
	int numberOf16KRomBanks() const;
	int numberOf8KVRomBanks() const;
	mirroringType mirroring() const;
	bool batteryBackedRam() const;
	bool hasTrainer() const;
	bool fourScreenVRamLayout() const;
	int romMapperType() const;
	bool vsSystemCartridges() const;
	int number8KBRamBanks() const;
	videoEncodingType videoEncoding() const;

private:
	intmax_t m_fileSize;
	bool m_valid;
	int m_numberOf16KRomBanks;
	int m_numberOf8KVRomBanks;
	mirroringType m_mirroring;
	bool m_batteryBackedRam;
	bool m_hasTrainer;
	bool m_fourScreenVRamLayout;
	int m_romMapperType;
	bool m_vsSystemCartridges;
	int m_number8KBRamBanks;
	videoEncodingType m_videoEncoding;
	Trainer m_trainer;
	std::vector<RomBank> m_romBanks;
	std::vector<VRomBank> m_vromBanks;
};
