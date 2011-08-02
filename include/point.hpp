#ifndef _POINT_
#define _POINT_

class Point
{
    public:
        double x;
        double y;

        Point();
        Point(const double& pX, const double& pY);
        Point& operator = (const Point& pPoint);
};

#endif
