#include "clap.h"
#include <stdio.h>


cLap::cLap(cActivity* lpParent)
{
	m_dwValid	= 0;
	m_lpParent	= lpParent;
}

cLap::cLap(cActivity* lpParent, const QDateTime &StartTime)
{
	m_dwValid	= 0;
	m_lpParent	= lpParent;
	setStartTime(StartTime);
}

cActivity* cLap::getParent()
{
	return(m_lpParent);
}

bool cLap::setStartTime(const QDateTime &StartTime)
{
	if(!StartTime.isValid())
		return(false);

	m_StartTime	= StartTime;
	m_dwValid	|= VALID_STARTTIME;
	return(true);
}

QDateTime cLap::getStartTime()
{
	if(m_dwValid & VALID_STARTTIME)
		return(m_StartTime);
	return(QDateTime(QDate(1980, 1, 1), QTime(0, 0)));
}

bool cLap::setTotalTime(double dTotalTime)
{
	m_dTotalTime	= dTotalTime;
	m_dwValid		|= VALID_TOTALTIME;
	return(true);
}

double cLap::getTotalTime()
{
	if(m_dwValid & VALID_TOTALTIME)
		return(m_dTotalTime);
	return(0);
}

bool cLap::setTotalDistance(double dTotalDistance)
{
	m_dTotalDistance	= dTotalDistance;
	m_dwValid			|= VALID_TOTALDISTANCE;
	return(true);
}

double cLap::getTotalDistance()
{
	if(m_dwValid & VALID_TOTALDISTANCE)
		return(m_dTotalDistance);
	return(0);
}

bool cLap::setMaximumSpeed(double dMaximumSpeed)
{
	m_dMaximumSpeed	= dMaximumSpeed;
	m_dwValid		|= VALID_MAXIMUMSPEED;
	return(true);
}

double cLap::getMaximumSpeed()
{
	if(m_dwValid & VALID_MAXIMUMSPEED)
		return(m_dMaximumSpeed);
	return(0);
}

bool cLap::setCalories(double dCalories)
{
	m_dCalories	= dCalories;
	m_dwValid	|= VALID_CALORIES;
	return(true);
}

double cLap::getCalories()
{
	if(m_dwValid & VALID_CALORIES)
		return(m_dCalories);
	return(0);
}

bool cLap::setAvgHeartrate(double dAvgHeartrate)
{
	m_dAvgHeartrate	= dAvgHeartrate;
	m_dwValid		|= VALID_AVGHEARTRATE;
	return(true);
}

double cLap::getAvgHeartrate()
{
	if(m_dwValid & VALID_AVGHEARTRATE)
		return(m_dAvgHeartrate);
	return(0);
}

bool cLap::setMaxHeartrate(double dMaxHeartrate)
{
	m_dMaxHeartrate	= dMaxHeartrate;
	m_dwValid		|= VALID_MAXHEARTRATE;
	return(true);
}

double cLap::getMaxHeartrate()
{
	if(m_dwValid & VALID_MAXHEARTRATE)
		return(m_dMaxHeartrate);
	return(0);
}

bool cLap::setIntensity(enum Intensity iIntensity)
{
	if(iIntensity < IntensityUnknown || iIntensity > IntensityNone)
		return(false);
	m_iIntensity	= iIntensity;
	m_dwValid		|= VALID_INTENSITY;
	return(true);
}

enum cLap::Intensity cLap::getIntensity()
{
	if(m_dwValid & VALID_INTENSITY)
		return(m_iIntensity);
	else
		return(cLap::IntensityNone);
}

bool cLap::setTriggerMethod(enum TriggerMethod iTriggerMethod)
{
	if(iTriggerMethod < TriggerMethodUnknown || iTriggerMethod > TriggerMethodNone)
		return(false);
	m_iTriggerMethod	= iTriggerMethod;
	m_dwValid			|= VALID_TRIGGERMETHOD;
	return(true);
}

enum cLap::TriggerMethod cLap::getTriggerMethod()
{
	if(m_dwValid & VALID_TRIGGERMETHOD)
		return(m_iTriggerMethod);
	else
		return(cLap::TriggerMethodNone);
}

cTrackpoint* cLap::addTrackpoint(uint32_t dwTime)
{
	return(m_TrackpointList.add(this, dwTime));
}

cLapList::cLapList()
{
}

cLap* cLapList::add(cActivity* lpParent, const QDateTime &StartTime)
{
	cLap*	lpLap	= new cLap(lpParent, StartTime);
	this->append(lpLap);
	return(lpLap);
}
