#include <matplotlibcpp17/pyplot.h>
#include "shortest_path_tsp.h"
#include <vector>


void plotPaths(vector<Point> &path)
{
	float x0, x1, y0, y1;
	pybind11::scoped_interpreter guard{};
  	auto plt = matplotlibcpp17::pyplot::import();

	auto [fig, ax] = plt.subplots(Kwargs("figsize"_a = py::make_tuple(10, 10)));
	ax.set_aspect(Args("equal"));
	for (unsigned int i = 0; i < path.size() - 1; i++)
	{
		x0 = path[i].x;
		y0 = path[i].y;
		x1 = path[i+1].x;
		y1 = path[i+1].y;
		ax.plot(Args(py::make_tuple(x0, x1), py::make_tuple(y0, y1)));
	}
  	plt.show();
}