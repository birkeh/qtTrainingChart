#ifndef CPOSITION_H
#define CPOSITION_H


class cPosition
{
public:
	cPosition(const cPosition& rhs);
	cPosition(double dLatitude = 0, double dLongitude = 0, double dElevation = 0);
	double		getLatitude();
	double		getLongitude();
	double		getElevation();
	cPosition&	operator=(const cPosition& rhs);
protected:
	double		m_dLatitude;
	double		m_dLongitude;
	double		m_dElevation;
};

#endif // CPOSITION_H
