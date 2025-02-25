#include <args_handle.h>
#include <vector>
#include <shortest_path_tsp.h>
#include <point.h>

using namespace std;

float defaultImprovementThreshold = 0.001;

void printArgs(ArgParams args)
{
	printf(
		"file name: %s\n"
		"start element: %d\n"
		"end element: %d\n"
		"threshold: %.4f\n",
		args.fileName.c_str(),
		args.startElement, args.endElement,
		args.improvementThreshold);
}

float parseArgumentFloat(string token)
{
	float value;
	try
	{
		value = stof(token);
	}
	catch (...)
	{
		printf("%s is invalid\n", token.c_str());
		return -1.0;
	}
	if (!((value > 0.0) & (value < 1.0)))
	{
		printf("threshold %.3f must be greater than zero and less than 1\n", value);
		value = -1.0;
	}
	return value;
}

int parseArgumentInt(string token)
{
	int value;
	try
	{
		value = stoi(token);
	}
	catch (...)
	{
		printf("%s is invalid\n", token.c_str());
		return -1;
	}
	if (value < 0)
	{
		printf("element: %d must be greater than zero\n", value);
		return -1;
	}
	return value;
}

ArgParams setArgs()
{
	ArgParams args;
	args.fileName = "./data/vps_set_1.csv";
	args.startElement = 0;
	args.endElement = 0;
	args.improvementThreshold = 0.001;
	printArgs(args);
	return args;
}

ArgParams parseArgs(int argc, char *argv[])
{
	ArgParams args;
	args.fileName = "";
	args.startElement = -1;
	args.endElement = -1;
	args.improvementThreshold = defaultImprovementThreshold;
	switch (argc)
	{
		case 1: // no arguments given
		{
			printf("No input file is given ...\n");
			break;
		}
		case 2: // only filename given
		{
			args.fileName = argv[1];
			args.startElement = 0;
			args.endElement = 0;
			args.improvementThreshold = defaultImprovementThreshold;
			break;
		}
		case 3: // filename and threshold given
		{
			args.fileName = argv[1];
			args.startElement = 0;
			args.endElement = 0;
			args.improvementThreshold = parseArgumentFloat(argv[2]);
			if (args.improvementThreshold < 0.0)
			{
				args.startElement = -1;
			}
			break;
		}
		case 4: // filename, start and end element given
		{
			args.fileName = argv[1];
			args.startElement = parseArgumentInt(argv[2]);
			args.endElement = parseArgumentInt(argv[3]);
			args.improvementThreshold = defaultImprovementThreshold;
			if (args.endElement == -1)
			{
				args.startElement = -1;
			}
			break;
		}
		case 5: // filename, start, end  and threshold given
		{
			args.fileName = argv[1];
			args.startElement = parseArgumentInt(argv[2]);
			args.endElement = parseArgumentInt(argv[3]);
			if (args.endElement == -1)
			{
				args.startElement = -1;
			}
			args.improvementThreshold = parseArgumentFloat(argv[4]);
			if (args.improvementThreshold < 0.0)
			{
				args.startElement = -1;
			}
			break;
		}
	}
	printArgs(args);
	if (args.startElement == -1)
	{
		printf("Invalid parameters ...");
		exit(-1);
	}
	return args;
}

// set index to the front of the path (start point)
void swapStartElement(int index, vector<Point> &path)
{
	if (index == 0) return;
	Point tmpPoint;
	tmpPoint = path.front();
	path.front() = path[index];
	path[index] = tmpPoint;
}

// set index to the back of the path (end point)
void swapEndElement(int index, vector<Point> &path)
{
	if (index == 0) return;
	Point tmpPoint;
	tmpPoint = path.back();
	path.back() = path[index];
	path[index] = tmpPoint;
}