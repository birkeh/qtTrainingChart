#include "cimport.h"
#include <math.h>


bool attributeString(const QDomElement& Element, const QString& szName, QString& szValue)
{
	QDomNamedNodeMap        Attributes      = Element.attributes();

	for(int z = 0;z < Attributes.count();z++)
	{
		QDomNode        Node    = Attributes.item(z);
		if(!Node.toAttr().name().compare(szName, Qt::CaseInsensitive))
		{
			szValue = Node.toAttr().nodeValue();
			return(true);
		}
	}
	return(false);
}

QDateTime toDateTime(const QString& szDateTime)
{
	QDateTime	DateTime = QDateTime::fromString(szDateTime, "yyyy-MM-ddTHH:mm:ss.000Z"); // 2011-04-17T07:04:35.000Z
	return(DateTime);
}

double toDouble(const QString& szDouble)
{
	QString sz = szDouble;
	bool bOk;
	double x;

	sz.replace(",", ".");
	x =  sz.toDouble(&bOk);
	if(!bOk)
	{
		sz.replace(".", ",");
		x =  sz.toDouble(&bOk);
	}
	return(x);
}

cImport::cImport()
{
}

QString cImport::getName()
{
	return("ImportTCX");
}

QString cImport::getVersion()
{
	return("1.0");
}

QString cImport::getExtension()
{
	return("Garmin Workouts (*.tcx)");
}

cActivityList cImport::getActivityList()
{
	return(m_ActivityList);
}

int32_t cImport::load(const QString &szFileName)
{
	if(!szFileName.contains(".tcx", Qt::CaseInsensitive))
		return(FILE_NOT_SUPPORTED);

	QFile			File(szFileName);
	if(!File.exists())
		return(FILE_NOT_EXIST);

	if(!szFileName.toLower().contains(".tcx"))
		return(FILE_WRONG_FORMAT);

	if(!File.open(QFile::ReadOnly | QFile::Text))
		return(FILE_NOT_READABLE);

	QDomDocument	Doc;
	QString			errorStr;
	int				errorLine;
	int				errorColumn;
	if(!Doc.setContent(&File, false, &errorStr, &errorLine, &errorColumn))
	{
		File.close();
		return(FILE_WRONG_FORMAT);
	}
	File.close();

	QDomElement		Root	= Doc.documentElement();

	if(Root.tagName().toLower() != "trainingcenterdatabase")
		return(FILE_WRONG_FORMAT);

	QDomNode		Child	= Root.firstChild();

	while(!Child.isNull())
	{
		if(!Child.toElement().tagName().compare("activities", Qt::CaseInsensitive))
			parseActivities(Child.toElement());
		else if(!Child.toElement().tagName().compare("author", Qt::CaseInsensitive))
			parseAuthor(Child.toElement());

		Child   = Child.nextSibling();
	}

	return(NO_ERROR);
}

void cImport::parseActivities(const QDomElement& Element)
{
	QDomNode		Child	= Element.firstChild();

	while(!Child.isNull())
	{
		if(!Child.toElement().tagName().compare("activity", Qt::CaseInsensitive))
		{
			QString	szSport;
			if(attributeString(Child.toElement(), "sport", szSport))
				parseActivity(Child.toElement(), szSport);
		}

		Child	= Child.nextSibling();
	}
}

void cImport::parseActivity(const QDomElement& Element, const QString& szSport)
{
	QDomNode					Child			= Element.firstChild();
	cActivity*					lpActivity		= 0;
	cActivity::ActivityType		iActivityType	= cActivity::ActivityTypeUnknown;

	if(!szSport.compare("running", Qt::CaseInsensitive))
		iActivityType	= cActivity::ActivityTypeRunning;
	else if(!szSport.compare("biking", Qt::CaseInsensitive))
		iActivityType	= cActivity::ActivityTypeBiking;

	while(!Child.isNull())
	{
		if(!Child.toElement().tagName().compare("id", Qt::CaseInsensitive))
		{
			if(lpActivity)
				lpActivity->setName(Child.toElement().text());
			else
				lpActivity	= m_ActivityList.add(iActivityType, Child.toElement().text());
		}
		else if(!Child.toElement().tagName().compare("lap", Qt::CaseInsensitive))
		{
			QString	szStartTime;
			if(attributeString(Child.toElement(), "starttime", szStartTime))
			{
				if(!lpActivity)
					lpActivity	= m_ActivityList.add(iActivityType, "EMPTY");
				cLap*	lpLap	= lpActivity->addLap(toDateTime(szStartTime));

				parseLap(Child.toElement(), lpLap);
			}
		}
		Child	= Child.nextSibling();
	}
}

void cImport::parseLap(const QDomElement& Element, cLap* lpLap)
{
	QDomNode	Child	= Element.firstChild();

	while(!Child.isNull())
	{
		if(!Child.toElement().tagName().compare("totaltimeseconds",Qt::CaseInsensitive))
			lpLap->setTotalTime(toDouble(Child.toElement().text()));
		else if(!Child.toElement().tagName().compare("distancemeters",Qt::CaseInsensitive))
			lpLap->setTotalDistance(toDouble(Child.toElement().text()));
		else if(!Child.toElement().tagName().compare("maximumspeed",Qt::CaseInsensitive))
			lpLap->setMaximumSpeed(toDouble(Child.toElement().text()));
		else if(!Child.toElement().tagName().compare("calories",Qt::CaseInsensitive))
			lpLap->setCalories(toDouble(Child.toElement().text()));
		else if(!Child.toElement().tagName().compare("averageheartratebpm",Qt::CaseInsensitive))
		{
			QDomNode	SubChild	= Child.toElement().firstChild();
			if(!SubChild.isNull())
				lpLap->setAvgHeartrate(toDouble(SubChild.toElement().text()));
		}
		else if(!Child.toElement().tagName().compare("maximumheartratebpm",Qt::CaseInsensitive))
		{
			QDomNode	SubChild	= Child.toElement().firstChild();
			if(!SubChild.isNull())
				lpLap->setMaxHeartrate(toDouble(SubChild.toElement().text()));
		}
		else if(!Child.toElement().tagName().compare("intensity",Qt::CaseInsensitive))
		{
			QString	sz	= Child.toElement().text();
			if(!sz.compare("active", Qt::CaseInsensitive))
				lpLap->setIntensity(cLap::IntensityActive);
			else
				lpLap->setIntensity(cLap::IntensityNone);
		}
		else if(!Child.toElement().tagName().compare("triggermethod",Qt::CaseInsensitive))
		{
			QString	sz	= Child.toElement().text();
			if(!sz.compare("manual", Qt::CaseInsensitive))
				lpLap->setTriggerMethod(cLap::TriggerMethodManual);
			else
				lpLap->setTriggerMethod(cLap::TriggerMethodNone);
		}
		else if(!Child.toElement().tagName().compare("track",Qt::CaseInsensitive))
			parseTrack(Child.toElement(), lpLap);

		Child	= Child.nextSibling();
	}
}

void cImport::parseTrack(const QDomElement& Element, cLap* lpLap)
{
	QDomNode		Child	= Element.firstChild();

	while(!Child.isNull())
	{
		if(!Child.toElement().tagName().compare("trackpoint", Qt::CaseInsensitive))
		{
			cTrackpoint*	lpTrackpoint	= lpLap->addTrackpoint(0);
			parseTrackpoint(Child.toElement(), lpTrackpoint);
		}

		Child	= Child.nextSibling();
	}
}

void cImport::parseTrackpoint(const QDomElement& Element, cTrackpoint* lpTrackpoint)
{
	QDomNode	Child	= Element.firstChild();
	double		dLatitude	= 0;
	double		dLongitude	= 0;
	double		dElevation	= 0;

	while(!Child.isNull())
	{
		if(!Child.toElement().tagName().compare("time", Qt::CaseInsensitive))
		{
			cLap*	lpLap	= lpTrackpoint->getParent();
			if(lpLap)
				lpTrackpoint->setTime(toDateTime(Child.toElement().text()).toTime_t()-lpLap->getStartTime().toTime_t());
		}
		else if(!Child.toElement().tagName().compare("position", Qt::CaseInsensitive))
		{
			QDomNode	subChild	= Child.toElement().firstChild();
			while(!subChild.isNull())
			{
				if(!subChild.toElement().tagName().compare("latitudedegrees", Qt::CaseInsensitive))
					dLatitude	= toDouble(subChild.toElement().text());
				else if(!subChild.toElement().tagName().compare("longitudedegrees", Qt::CaseInsensitive))
					dLongitude	= toDouble(subChild.toElement().text());
				subChild	= subChild.nextSibling();
			}
		}
		else if(!Child.toElement().tagName().compare("altitudemeters", Qt::CaseInsensitive))
			dElevation	= toDouble(Child.toElement().text());
		else if(!Child.toElement().tagName().compare("distancemeters", Qt::CaseInsensitive))
			lpTrackpoint->setDistance(toDouble(Child.toElement().text()));
		else if(!Child.toElement().tagName().compare("heartratebpm", Qt::CaseInsensitive))
		{
			QDomNode	SubChild	= Child.toElement().firstChild();
			if(!SubChild.isNull())
				lpTrackpoint->setHeartRate(toDouble(SubChild.toElement().text()));
		}

		Child	= Child.nextSibling();
	}
	lpTrackpoint->setPosition(cPosition(dLatitude, dLongitude, dElevation));
}

void cImport::parseAuthor(const QDomElement& Element)
{
}

extern "C"
{
	cImport* create()
	{
		return(new cImport);
	}

	void destroy(cImport* p)
	{
		delete p;
	}
}
