#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

#include "NesFile.hpp"
#include "Exceptions.hpp"

NesFile::NesFile(const std::string& file, bool pedanticMode) : m_valid(false)
{
	LoadFile(file, pedanticMode);
}

void NesFile::LoadFile(const std::string& file, bool pedanticMode)
{
	struct stat statbuf;
    if (stat(file.c_str(), &statbuf) == -1)
	{
		throw CannotDetermineFileSizeException();
	}

#ifdef __GNUC__
	FILE * fp = fopen(file.c_str(), "rb");
#elif defined WIN32
	FILE * fp;
	fopen_s(&fp, file.c_str(), "rb");
#endif

	if (fp == NULL)
	{
		throw FileNotFoundException();
	}

	intmax_t fileSize = statbuf.st_size;
	m_fileSize = fileSize;

	unsigned char* fileData;
	unsigned char* fileDataBegin;

	fileData = new unsigned char[fileSize];
	fileDataBegin = fileData;

	size_t readResult = fread(fileData, 1, fileSize, fp);

    fclose(fp);

	if ((readResult != fileSize) || (readResult < commonValues::_HeaderSize))
	{
		m_valid = false;
		delete[] fileDataBegin;
		return;
	}

	const unsigned char headerMagicNumber[4]={0x4E, 0x45, 0x53, 0x1A};
	int compareResult = memcmp(fileData, headerMagicNumber, 4);
	if (compareResult != 0)
	{
		m_valid = false;
		delete[] fileDataBegin;
		return;
	}

	m_numberOf16KRomBanks = fileData[4];
	m_numberOf8KVRomBanks = fileData[5];

	int byte6 = fileData[6];
	//bit 0     1 for vertical mirroring, 0 for horizontal mirroring.
    //bit 1     1 for battery-backed RAM at $6000-$7FFF.
    //bit 2     1 for a 512-byte trainer at $7000-$71FF.
    //bit 3     1 for a four-screen VRAM layout.
    //bit 4-7   Four lower bits of ROM Mapper Type.
	m_mirroring            = ((byte6 & 0x1) != 0) ? VERTICAL : HORIZONTAL;
	m_batteryBackedRam     = ((byte6 & 0x2) != 0);
	m_hasTrainer           = ((byte6 & 0x4) != 0);
	m_fourScreenVRamLayout = ((byte6 & 0x8) != 0);

	m_romMapperType = 0;
	m_romMapperType |= (byte6 >> 4);

	int byte7 = fileData[7];
	//bit 0     1 for VS-System cartridges.
    //bit 1-3   Reserved, must be zeroes!
    //bit 4-7   Four higher bits of ROM Mapper Type.
	m_vsSystemCartridges   = ((byte7 & 0x1) != 0);
	bool byte7ReserverBits = ((byte7 & 0xE) == 0);
	if ((pedanticMode == true) && (byte7ReserverBits == false))
	{
    	m_valid = false;
		delete[] fileDataBegin;
		return;
	}

	m_romMapperType |= (byte7 & 0xF0);

	m_number8KBRamBanks = (fileData[8] != 0) ? fileData[8] : 1;

	m_videoEncoding = ((fileData[9] & 0x1) == 1) ? PAL : NTSC;
	if ((pedanticMode == true) && ((fileData[9] & 0xFE) != 0))
	{
        m_valid = false;
		delete[] fileDataBegin;
		return;
	}

    const unsigned char headerReservedBytes[6] = {0x0,0x0,0x0,0x0,0x0,0x0};
	compareResult = memcmp((fileData+0xA), headerReservedBytes, 6);
	if (compareResult != 0)
	{
	    if (pedanticMode == true)
	    {
        m_valid = false;
		delete[] fileDataBegin;
		return;
		}
		else
		{
			// Em caso de ROM antiga que contem lixo
			// do byte 7 ao 15, limpa os 4 bits mais
			// significativos e segue.
			m_romMapperType &= 0xF;
		}
	}

	int totalSize = commonValues::_HeaderSize +
		            (m_numberOf16KRomBanks*commonValues::_16K) +
					(m_numberOf8KVRomBanks*commonValues::_8K) +
					((m_hasTrainer == true) ? commonValues::_512B : 0);

	if (totalSize > fileSize)
	{
		m_valid = false;
		delete[] fileDataBegin;
		return;
	}

	fileData += commonValues::_HeaderSize;

	if (m_hasTrainer == true)
	{
	    m_trainer.assign(fileData);
		fileData += (commonValues::_512B);
	}

	m_romBanks.reserve(m_numberOf16KRomBanks);
	m_romBanks.assign(m_numberOf16KRomBanks, RomBank());
	for (int i = 0; i < m_numberOf16KRomBanks; i++)
	{
		RomBank& romBank = m_romBanks[i];
		romBank.assign(fileData);
		fileData += commonValues::_16K;
	}

	m_vromBanks.reserve(m_numberOf8KVRomBanks);
	m_vromBanks.assign(m_numberOf8KVRomBanks, VRomBank());
	for (int i = 0; i < m_numberOf8KVRomBanks; i++)
	{
		VRomBank& vromBank = m_vromBanks[i];
		vromBank.assign(fileData);
		fileData += commonValues::_8K;
	}

	delete[] fileDataBegin;

    m_valid = true;
}

intmax_t NesFile::fileSize() const
{
	return m_fileSize;
}

bool NesFile::valid() const
{
	return m_valid;
}

int NesFile::numberOf16KRomBanks() const
{
	return m_numberOf16KRomBanks;
}

int NesFile::numberOf8KVRomBanks() const
{
	return m_numberOf8KVRomBanks;
}

NesFile::mirroringType NesFile::mirroring() const
{
	return m_mirroring;
}

bool NesFile::batteryBackedRam() const
{
	return m_batteryBackedRam;
}

bool NesFile::hasTrainer() const
{
	return m_hasTrainer;
}

bool NesFile::fourScreenVRamLayout() const
{
	return m_fourScreenVRamLayout;
}

int NesFile::romMapperType() const
{
	return m_romMapperType;
}

bool NesFile::vsSystemCartridges() const
{
	return m_vsSystemCartridges;
}

int NesFile::number8KBRamBanks() const
{
	return m_number8KBRamBanks;
}

NesFile::videoEncodingType NesFile::videoEncoding() const
{
	return m_videoEncoding;
}
