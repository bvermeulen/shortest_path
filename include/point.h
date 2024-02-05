/*
header for point.cpp
*/
#ifndef POINT_H
#define POINT_H
#include <sstream>

using namespace std;

class Point
{
public:
    string id;
    float x, y;

    Point(string id, float x, float y);
    Point();
    float dist(const Point &other) const;
    float angle(const Point &other) const;
};

#endif // POINT_H