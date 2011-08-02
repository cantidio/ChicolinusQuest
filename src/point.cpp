#include "point.hpp"

Point::Point()
{
	x = 0;
    y = 0;
}

Point::Point(const double& pX, const double& pY)
{
    x = pX;
    y = pY;
}

Point& Point::operator = (const Point& pPoint)
{
	x = pPoint.x;
	y = pPoint.y;
	return *this;
}
