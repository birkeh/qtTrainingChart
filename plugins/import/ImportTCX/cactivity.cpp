#include "cactivity.h"
#include <stdio.h>


cActivity::cActivity()
{
	m_dwValid	= 0;
}

cActivity::cActivity(const cActivity& rhs)
{
	this->m_dwValid			= rhs.m_dwValid;
	this->m_iActivityType	= rhs.m_iActivityType;
	this->m_LapList			= rhs.m_LapList;
	this->m_szName			= rhs.m_szName;
}

cActivity::cActivity(enum ActivityType iActivityType, const QString& szName)
{
	m_dwValid	= 0;
	setActivityType(iActivityType);
	setName(szName);
}

bool cActivity::setActivityType(enum ActivityType iActivityType)
{
	if(iActivityType < ActivityTypeUnknown || iActivityType > ActivityTypeNone)
		return(false);
	m_iActivityType	= iActivityType;
	m_dwValid		|= VALID_ACTIVITYTYPE;
	return(true);
}

enum cActivity::ActivityType cActivity::getActivityType()
{
	if(m_dwValid & VALID_ACTIVITYTYPE)
		return(m_iActivityType);
	else
		return(ActivityTypeUnknown);
}

bool cActivity::setName(const QString& szName)
{
	if(!szName.length())
		return(false);

	m_szName	= szName;
	m_dwValid	|= VALID_NAME;
	return(true);
}

QString cActivity::getName()
{
	if(m_dwValid & VALID_NAME)
		return(m_szName);
	return("");
}

cLap* cActivity::addLap(const QDateTime& StartTime)
{
	return(m_LapList.add(this, StartTime));
}

cLapList cActivity::getLapList()
{
	return(m_LapList);
}

cActivity& cActivity::operator=(const cActivity& rhs)
{
	if(this != &rhs)
	{
		this->m_dwValid			= rhs.m_dwValid;
		this->m_iActivityType	= rhs.m_iActivityType;
		this->m_LapList			= rhs.m_LapList;
		this->m_szName			= rhs.m_szName;
	}
	return(*this);
}

cActivityList::cActivityList()
{
}

cActivity* cActivityList::add(enum cActivity::ActivityType iActivityType, const QString& szName)
{
	cActivity*	lpActivity	= new cActivity(iActivityType, szName);
	this->append(lpActivity);
	return(lpActivity);
}
