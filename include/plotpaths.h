#ifndef PLOTPATHS
#define PLOTPATHS

#include "point.h"


class PlotPaths
{
private:
	int counter;

public:
	PlotPaths();
	void plotFullPath(const Point* path, int nPoints);
	void Blit(float pauseSeconds);
	void Show();
	void Save();
};
#endif // PLOTPATHS