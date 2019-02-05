#include "Trainer.hpp"
#include "commonvalues.hpp"

Trainer::Trainer()
{
    m_bank.reserve(commonValues::_512B);
}

Trainer::Trainer(const Trainer& copy)
{
    m_bank.reserve(commonValues::_512B);

    m_bank.assign(copy.m_bank.begin(), copy.m_bank.end());
}

Trainer& Trainer::operator=(const Trainer& rhs)
{
    m_bank.assign(rhs.m_bank.begin(), rhs.m_bank.end());

	return (*this);
}

Trainer& Trainer::operator=(const unsigned char * buffer)
{
    m_bank.assign(buffer, (buffer+commonValues::_512B));

	return (*this);
}

void Trainer::assign(const unsigned char * buffer)
{
    m_bank.assign(buffer, (buffer+commonValues::_512B));
}

const unsigned char& Trainer::operator[](int index) const
{
    if ((index < 0) || (index >= commonValues::_512B))
	{
	    ;// lancar uma exception? matar o treco? chorar?
	}

	return m_bank[index];
}

const std::vector<unsigned char>& Trainer::getBankVector() const
{
    return m_bank;
}

const unsigned char* Trainer::getBankBuffer() const
{
    return &m_bank[0];
}
