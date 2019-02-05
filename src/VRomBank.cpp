#include "VRomBank.hpp"
#include "commonvalues.hpp"

VRomBank::VRomBank()
{
    m_bank.reserve(commonValues::_8K);
}

VRomBank::VRomBank(const VRomBank& copy)
{
    m_bank.reserve(commonValues::_8K);

    m_bank.assign(copy.m_bank.begin(), copy.m_bank.end());
}

VRomBank& VRomBank::operator=(const VRomBank& rhs)
{
    m_bank.assign(rhs.m_bank.begin(), rhs.m_bank.end());

	return (*this);
}

VRomBank& VRomBank::operator=(const unsigned char * buffer)
{
    m_bank.assign(buffer, (buffer+commonValues::_8K));

	return (*this);
}

void VRomBank::assign(const unsigned char * buffer)
{
    m_bank.assign(buffer, (buffer+commonValues::_8K));
}

const unsigned char& VRomBank::operator[](int index) const
{
    if ((index < 0) || (index >= commonValues::_8K))
	{
	    ;// lancar uma exception? matar o treco? chorar?
	}

	return m_bank[index];
}

const std::vector<unsigned char>& VRomBank::getBankVector() const
{
    return m_bank;
}

const unsigned char* VRomBank::getBankBuffer() const
{
    return &m_bank[0];
}
