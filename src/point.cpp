/*
Class definition of Point
*/
#include <point.h>
#include <math.h>
#include <shortest_path_tsp.h>

Point::Point(string id, float x, float y)
{
    this->id = id;
    this->x = x;
    this->y = y;
}
Point::Point()
{
    this->id = "0";
    this->x = 0.0;
    this->y = 0.0;
}
//// Distance between two points
float Point::dist(const Point &other) const
{
    return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}
// Angle of the vector between two points with the x-axis
float Point::angle(const Point &other) const
{
    float angle;
    angle = rad_deg * atan2(other.y - y, other.x - x);
    if (angle < 0.0)
        angle += 360;
    if (angle > 180.0)
        angle = abs(angle - 360.0);
    if (angle > 90.0)
        angle = abs(angle - 180.0);
    return angle;
}

