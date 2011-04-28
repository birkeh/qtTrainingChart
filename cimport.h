#ifndef CIMPORT_H
#define CIMPORT_H


#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QDateTime>
#include <stdint.h>

#include "cactivity.h"
#include "clap.h"
#include "ctrackpoint.h"


class cImport
{
public:
	enum IMPORT_ERROR
	{
		NO_ERROR			= 0,
		FILE_NOT_EXIST		= 1,
		FILE_NOT_SUPPORTED	= 2,
		FILE_NOT_READABLE	= 3,
		FILE_WRONG_FORMAT	= 4,
	};

	cImport();

	virtual QString			getName();
	virtual QString			getVersion();
	virtual QString			getExtension();
	virtual cActivityList	getActivityList();

	virtual int32_t			load(const QString& szFileName);

protected:
	cActivityList	m_ActivityList;
};

typedef cImport*	create_t();
typedef void		destroy_t(cImport* lpImport);

#endif // CIMPORT_H
