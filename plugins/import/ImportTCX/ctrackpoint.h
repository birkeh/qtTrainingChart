#ifndef CTRACKPOINT_H
#define CTRACKPOINT_H


#include <stdint.h>
#include <QMetaType>
#include <QString>
#include <QDateTime>

#include "common.h"

#include "cposition.h"


class cLap;

class cTrackpoint
{
public:
	cTrackpoint(cLap* lpParent = 0);
	cTrackpoint(cLap* lpParent, uint32_t dwTime);

	cLap*		getParent();

	bool		setTime(uint32_t dwTime);
	uint32_t	getTime();

	bool		setPosition(const cPosition& Position);
	cPosition	getPosition();

	bool		setDistance(double dDistance);
	double		getDistance();

	bool		setHeartRate(uint16_t dwHeartRate);
	uint16_t	getHeartRate();
protected:
	uint64_t	m_dwValid;
	cLap*		m_lpParent;
	uint32_t	m_dwTime;
	cPosition	m_Position;
	double		m_dDistance;
	uint16_t	m_dwHeartRate;
};

Q_DECLARE_METATYPE(cTrackpoint);

class cTrackpointList : public QList<cTrackpoint*>
{
public:
	cTrackpointList();
	cTrackpoint*	add(cLap* lpParent, uint32_t dwTime);
};
#endif // CTRACKPOINT_H
