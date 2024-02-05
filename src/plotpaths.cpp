#include <matplotlibcpp17/pyplot.h>
#include <sstream>
#include <point.h>
#include <plotpaths.h>
#include <vector>

pybind11::scoped_interpreter guard{};
auto plt = matplotlibcpp17::pyplot::import();
auto [fig, ax] = plt.subplots(Kwargs("figsize"_a = py::make_tuple(10, 10)));

PlotPaths::PlotPaths()
{
	this->counter = 0;
}

void PlotPaths::plotFullPath(vector<Point> &path)
{
	float x0, x1, y0, y1;
	ax.set_aspect(Args("equal"));
	for (unsigned int i = 0; i < path.size() - 1; i++)
	{
		x0 = path[i].x;
		y0 = path[i].y;
		x1 = path[i+1].x;
		y1 = path[i+1].y;
		ax.plot(Args(py::make_tuple(x0, x1), py::make_tuple(y0, y1)));
	}
	this->counter += 1;
};

void PlotPaths::Blit(float pauseSeconds) {
	plt.pause(Args(pauseSeconds));
	ax.cla();
};

void PlotPaths::Show() {
	plt.show();
};

void PlotPaths::Save() {
	string baseFileName = "shortest_path_tsp_";
	string const OutFile = baseFileName + to_string(this->counter) + ".png";
 	fig.savefig(Args(OutFile.c_str()));
};