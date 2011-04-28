#ifndef CACTIVITY_H
#define CACTIVITY_H


#include <stdint.h>
#include <QMetaType>
#include <QString>

#include "common.h"
#include "clap.h"


class cActivity
{
public:
	enum ActivityType
	{
		ActivityTypeUnknown,
		ActivityTypeRunning,
		ActivityTypeBiking,
		ActivityTypeSwimming,
		ActivityTypeNone,
	};

	cActivity();
	cActivity(const cActivity& rhs);
	cActivity(enum ActivityType iActivityType, const QString& szName);

	bool				setActivityType(enum ActivityType iActivityType);
	enum ActivityType	getActivityType();

	bool				setName(const QString& szName);
	QString				getName();

	cLap*				addLap(const QDateTime& StartTime);
	cLapList			getLapList();

	cActivity&			operator=(const cActivity& rhs);
protected:
	uint64_t			m_dwValid;
	enum ActivityType	m_iActivityType;
	QString				m_szName;

	cLapList			m_LapList;
};

Q_DECLARE_METATYPE(cActivity);

class cActivityList : public QList<cActivity*>
{
public:
	cActivityList();
	cActivity*	add(enum cActivity::ActivityType iActivityType, const QString& szName);
};

#endif // CACTIVITY_H
