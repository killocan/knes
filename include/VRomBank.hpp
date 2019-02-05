#pragma once

#include <vector>

class VRomBank
{
public:
	VRomBank();
	VRomBank(const VRomBank& copy);

	VRomBank& operator=(const VRomBank& rhs);
	VRomBank& operator=(const unsigned char * buffer);

	void assign(const unsigned char * buffer);

	const unsigned char& operator[](int index) const;

	const std::vector<unsigned char>& getBankVector() const;
	const unsigned char* getBankBuffer() const;

private:
	std::vector<unsigned char> m_bank;
};
