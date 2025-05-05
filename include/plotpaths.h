#ifndef PLOTPATHS
#define PLOTPATHS

#include "point.h"
#include <vector>


class PlotPaths
{
private:
	int counter;

public:
	PlotPaths();
	void plotFullPath(const vector<Point> &path);
	void Blit(float pauseSeconds);
	void Show();
	void Save();
};

#endif // PLOTPATHS