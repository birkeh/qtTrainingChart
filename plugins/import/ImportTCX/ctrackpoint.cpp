#include "ctrackpoint.h"


cTrackpoint::cTrackpoint(cLap* lpParent)
{
	m_dwValid	= 0;
	m_lpParent	= lpParent;
}

cTrackpoint::cTrackpoint(cLap* lpParent, uint32_t dwTime)
{
	m_dwValid	= 0;
	m_lpParent	= lpParent;
	setTime(dwTime);
}

cLap* cTrackpoint::getParent()
{
	return(m_lpParent);
}

bool cTrackpoint::setTime(uint32_t dwTime)
{
	m_dwTime	= dwTime;
	m_dwValid	|= VALID_TIME;
	return(true);
}

uint32_t cTrackpoint::getTime()
{
	if(m_dwValid & VALID_TIME)
		return(m_dwTime);
	return(0);
}

bool cTrackpoint::setPosition(const cPosition& Position)
{
	m_Position	= Position;
	m_dwValid	|= VALID_POSITION;
	return(true);
}

cPosition cTrackpoint::getPosition()
{
	if(m_dwValid & VALID_POSITION)
		return(m_Position);
	return(cPosition(0, 0));
}

bool cTrackpoint::setDistance(double dDistance)
{
	m_dDistance	= dDistance;
	m_dwValid	|= VALID_DISTANCE;
	return(true);
}

double cTrackpoint::getDistance()
{
	if(m_dwValid & VALID_DISTANCE)
		return(m_dDistance);
	else
		return(0);
}

bool cTrackpoint::setHeartRate(uint16_t dwHeartRate)
{
	if(!dwHeartRate)
		return(false);

	m_dwHeartRate	= dwHeartRate;
	m_dwValid		|= VALID_HEARTRATE;
	return(true);
}

uint16_t cTrackpoint::getHeartRate()
{
	if(m_dwValid & VALID_HEARTRATE)
		return(m_dwHeartRate);
	return(0);
}

cTrackpointList::cTrackpointList()
{
}

cTrackpoint* cTrackpointList::add(cLap* lpParent, uint32_t dwTime)
{
	cTrackpoint*	lpTrackpoint	= new cTrackpoint(lpParent, dwTime);
	this->append(lpTrackpoint);
	return(lpTrackpoint);
}
