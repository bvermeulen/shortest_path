#ifndef PLOTPATHS
#define PLOTPATHS
#include <matplotlibcpp17/pyplot.h>
#include "point.h"


class PlotPaths
{
private:
	int counter;
	matplotlibcpp17::pyplot::PyPlot plt = matplotlibcpp17::pyplot::import();
	matplotlibcpp17::figure::Figure fig = plt.figure(Kwargs("figsize"_a = py::make_tuple(7, 7)));
	matplotlibcpp17::axes::Axes ax = fig.add_subplot();

public:
	PlotPaths();
	void plotFullPath(const Point* path, int nPoints);
	void Blit(float pauseSeconds);
	void Show();
	void Save();
};
#endif // PLOTPATHS