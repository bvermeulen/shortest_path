#include <plotpaths.h>
#include <shortest_path_tsp.h>
#include <point.h>


PlotPaths::PlotPaths()
{
	counter = 0;
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
	counter++;
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
	string const OutFile = pngBaseFileName + to_string(counter) + ".png";
	fig.savefig(Args(OutFile.c_str()));
};