#pragma once

#include <vector>

class RomBank
{
public:
	RomBank();
	RomBank(const RomBank& copy);
	
	RomBank& operator=(const RomBank& rhs);
	RomBank& operator=(const unsigned char * buffer);

	void assign(const unsigned char * buffer);

	const unsigned char& operator[](int index) const;

	const std::vector<unsigned char>& getBankVector() const;
	const unsigned char* getBankBuffer() const;

private:
	std::vector<unsigned char> m_bank;
};
