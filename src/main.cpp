#include <string>
#include <exception>
#include <iostream>

#include "NesFile.hpp"

int main(int argc, char *argv[])
{
	std::string file = "c:\\megaman.nes";
	//std::string file = "c:\\mariobros.nes";
	//std::string file = "c:\\legendofzelda.nes";
	try
	{
		NesFile nesObj(file, true);

		std::cout << "File name: ["               << file                          << "]\n";
		std::cout << "File size: ["               << nesObj.fileSize()             << "]\n";
		std::cout << "Valid Nes ROM: ["           << nesObj.valid()                << "]\n";
		std::cout << "Number of 16K ROM Banks: [" << nesObj.numberOf16KRomBanks()  << "]\n";
		std::cout << "Number of 8K VROM Banks: [" << nesObj.numberOf8KVRomBanks()  << "]\n";

		std::cout << "Mirroring: ["               << ((nesObj.mirroring()==NesFile::VERTICAL) ? "VERTICAL" : "HORIZONTAL") << "]\n";

		std::cout << "Battery Backed RAM: ["      << nesObj.batteryBackedRam()     << "]\n";
		std::cout << "Trainer: ["                 << nesObj.hasTrainer()           << "]\n";
		std::cout << "Four Screen VRAM Layout: [" << nesObj.fourScreenVRamLayout() << "]\n";
		std::cout << "Mapper: ["                  << nesObj.romMapperType()        << "]\n";
		std::cout << "VS System Cartridges: ["    << nesObj.vsSystemCartridges()   << "]\n";
		std::cout << "Number 8KB RAM Banks: ["    << nesObj.number8KBRamBanks()    << "]\n";

		std::cout << "Video Encoding: ["          << ((nesObj.videoEncoding()==NesFile::PAL) ? "PAL" : "NTSC") << "]\n";
	}
	catch(std::exception& e)
	{
		std::cerr << e.what();
	}

    return 0;
}
