#include "RomBank.hpp"
#include "commonvalues.hpp"

RomBank::RomBank()
{
    m_bank.reserve(commonValues::_16K);
}

RomBank::RomBank(const RomBank& copy)
{
	m_bank.reserve(commonValues::_16K);

	m_bank.assign(copy.m_bank.begin(), copy.m_bank.end());
}

RomBank& RomBank::operator=(const RomBank& rhs)
{
	m_bank.assign(rhs.m_bank.begin(), rhs.m_bank.end());

	return (*this);
}

RomBank& RomBank::operator=(const unsigned char * buffer)
{
    m_bank.assign(buffer, (buffer+commonValues::_16K));

	return (*this);
}

void RomBank::assign(const unsigned char * buffer)
{
    m_bank.assign(buffer, (buffer+commonValues::_16K));
}

const unsigned char& RomBank::operator[](int index) const
{
    if ((index < 0) || (index >= commonValues::_16K))
	{
	    ;// lancar uma exception? matar o treco? chorar?
    }

	return m_bank[index];
}

const std::vector<unsigned char>& RomBank::getBankVector() const
{
    return m_bank;
}

const unsigned char* RomBank::getBankBuffer() const
{
    return &m_bank[0];
}
