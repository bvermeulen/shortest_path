#include <matplotlibcpp17/pyplot.h>
#include "point.h"
#include <vector>

pybind11::scoped_interpreter guard{};

auto plt = matplotlibcpp17::pyplot::import();
auto [fig, ax] = plt.subplots(Kwargs("figsize"_a = py::make_tuple(10, 10)));

class PlotPaths
{
	int counter;

public:
	PlotPaths() {
		this->counter = 0;
	}

	inline void plotMyPath(vector<Point> &path)
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
		string filename = "./path_plot.png";
		string outfile = filename.substr(0, filename.find_last_of(".png") - 3) + "_" + to_string(this->counter) + ".png";
		printf("plot counter is: %s", outfile.c_str());
  		fig.savefig(Args(outfile));
	}

	inline void Blit(float pauseSeconds) {
		plt.pause(Args(pauseSeconds));
		ax.cla();

	}

	inline void Show() {
		plt.show();
	}
};

//void plotPaths(vector<Point> &path);

