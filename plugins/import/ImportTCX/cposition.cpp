#include "cposition.h"


cPosition::cPosition(const cPosition& rhs)
{
	this->m_dLatitude	= rhs.m_dLatitude;
	this->m_dLongitude	= rhs.m_dLongitude;
	this->m_dElevation	= rhs.m_dElevation;
}

cPosition::cPosition(double dLatitude, double dLongitude, double dElevation)
{
	m_dLatitude		= dLatitude;
	m_dLongitude	= dLongitude;
	m_dElevation	= dElevation;
}

double cPosition::getLatitude()
{
	return(m_dLatitude);
}

double cPosition::getLongitude()
{
	return(m_dLongitude);
}

double cPosition::getElevation()
{
	return(m_dElevation);
}

cPosition	&cPosition::operator=(const cPosition &rhs)
{
	if(this != &rhs)
	{
		this->m_dLatitude	= rhs.m_dLatitude;
		this->m_dLongitude	= rhs.m_dLongitude;
		this->m_dElevation	= rhs.m_dElevation;
	}
	return(*this);
}
