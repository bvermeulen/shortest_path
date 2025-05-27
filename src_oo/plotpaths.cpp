#include <plotpaths.h>
#include <matplotlibcpp17/pyplot.h>
#include <../include_oo/shortest_path_tsp.h>
#include <../include_oo/point.h>

pybind11::scoped_interpreter guard{};
pybind11::module site = pybind11::module::import("site");
auto result = site.attr("addsitedir")("/home/bvermeulen/Python/venv/lib/python3.13/site-packagesc");
auto plt = matplotlibcpp17::pyplot::import();
auto [fig, ax] = plt.subplots(Kwargs("figsize"_a = py::make_tuple(7, 7)));

PlotPaths::PlotPaths()
{
	this->counter = 0;
}

void PlotPaths::plotFullPath(const Point* path, int nPoints)
{
	float x0, x1, y0, y1;
	ax.set_aspect(Args("equal"));
	for (int i = 0; i < nPoints - 1; i++)
	{
		x0 = path[i].x;
		y0 = path[i].y;
		x1 = path[i + 1].x;
		y1 = path[i + 1].y;
		ax.plot(Args(py::make_tuple(x0, x1), py::make_tuple(y0, y1)));
	}
	this->counter += 1;
};

void PlotPaths::Blit(float pauseSeconds)
{
	plt.pause(Args(pauseSeconds));
	ax.cla();
};

void PlotPaths::Show()
{
	plt.show();
};

void PlotPaths::Save()
{
	string const OutFile = pngBaseFileName + to_string(this->counter) + ".png";
	fig.savefig(Args(OutFile.c_str()));
};