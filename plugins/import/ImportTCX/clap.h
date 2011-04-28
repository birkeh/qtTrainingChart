#ifndef CLAP_H
#define CLAP_H


#include <stdint.h>
#include <QMetaType>
#include <QString>
#include <QDateTime>

#include "common.h"

#include "ctrackpoint.h"


class cActivity;

class cLap
{
public:
	enum Intensity
	{
		IntensityUnknown,
		IntensityActive,
		IntensityNone,
	};

	enum TriggerMethod
	{
		TriggerMethodUnknown,
		TriggerMethodManual,
		TriggerMethodAuto,
		TriggerMethodNone,
	};

	cLap(cActivity* lpParent = 0);
	cLap(cActivity* lpParent, const QDateTime& StartTime);

	cActivity*			getParent();

	bool				setStartTime(const QDateTime& StartTime);
	QDateTime			getStartTime();

	bool				setTotalTime(double dTotalTime);
	double				getTotalTime();

	bool				setTotalDistance(double dTotalDistance);
	double				getTotalDistance();

	bool				setMaximumSpeed(double dMaximumSpeed);
	double				getMaximumSpeed();

	bool				setCalories(double dCalories);
	double				getCalories();

	bool				setAvgHeartrate(double dAvgHeartrate);
	double				getAvgHeartrate();

	bool				setMaxHeartrate(double dMaxHeartrate);
	double				getMaxHeartrate();

	bool				setIntensity(enum Intensity iIntensity);
	enum Intensity		getIntensity();

	bool				setTriggerMethod(enum TriggerMethod iTriggerMethod);
	enum TriggerMethod	getTriggerMethod();

	cTrackpoint*		addTrackpoint(uint32_t dwTime);
protected:
	uint64_t			m_dwValid;
	cActivity*			m_lpParent;
	QDateTime			m_StartTime;
	double				m_dTotalTime;
	double				m_dTotalDistance;
	double				m_dMaximumSpeed;
	double				m_dCalories;
	double				m_dAvgHeartrate;
	double				m_dMaxHeartrate;
	enum Intensity		m_iIntensity;
	enum TriggerMethod	m_iTriggerMethod;
	cTrackpointList		m_TrackpointList;
};

Q_DECLARE_METATYPE(cLap);

class cLapList : public QList<cLap*>
{
public:
	cLapList();
	cLap*	add(cActivity* lpParent, const QDateTime& StartTime);
};

#endif // CLAP_H
