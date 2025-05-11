#include <bits/stdc++.h>
#include <../include_oo/args_handle.h>
#include <../include_oo/point.h>
#include <../include_oo/csv.h>

using namespace std;

float defaultImprovementThreshold = 0.001;
bool defaultPrintData = false;

string getFileName(int argc, char *arg[])
{
	if (argc == 1)
	{
		printf("No input file is given ...\n");
		exit(0);
	}
	printf("file name: %s\n", arg[1]);
	return arg[1];
}

float parseArgumentThreshold(string token)
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

int parseArgumentIndex(string token, const Column *csvData, int nPoints)
{
	int value;

	string firstLetter(1, token.front());
	if ((token.find(".") != string::npos) & (firstLetter != "L"))
	{
		printf("Index: %s must be an integer or start with an L\n", token.c_str());
		return -1;
	}
	try
	{
		value = stoi(token);
		if (value < 0)
		{
			printf("Index: %d must be greater than zero\n", value);
			return -1;
		}

		if (value > nPoints - 1)
		{
			printf("Index %d must be less than %d\n", value, nPoints);
			return -1;
		}
		return value;
	}
	catch (...)
	{
		// token is not an integer
		value = -1;
	}

	// check if token is a label, a label must start with 'L"
	if (firstLetter == "L")
	{
		string label = token.substr(1, token.size());
		for (int i = 0; i < nPoints; i++)
		{
			if (label == csvData[0].colValues[i])
			{
				value = i;
				break;
			}
		}
		if (value == -1)
		{
			printf("Label %s does not exist\n", label.c_str());
		}
	}
	else
	{
		printf("Index %s must be an integer or start with an L\n", token.c_str());
	}
	return value;
}

void printArgs(ArgParams args)
{
	printf(
		"start index: %d\n"
		"end index: %d\n"
		"number points: %d\n"
		"threshold: %.4f\n"
		"print: %s\n",
		args.startIndex,
		args.endIndex,
		args.nPoints,
		args.improvementThreshold,
		args.printData ? "yes" : "no");
}

ArgParams parseArgs(int argc, char *argv[], Csv csv)
{
	ArgParams args;
	args.startIndex = -1;
	args.endIndex = -1;
	args.improvementThreshold = defaultImprovementThreshold;
	args.printData = defaultPrintData;
	int nPoints = csv.getRows();
	args.nPoints = nPoints;
	Column* csvData = csv.getCsvData();

	switch (argc)
	{
	case 1:
	{
		// No input file
		printf("No input file is given ...\n");
		break;
	}
	case 2:
	{
		// only filename given
		args.startIndex = 0;
		args.endIndex = nPoints - 1;
		break;
	}
	case 3:
	{
		// filename, threshold or
		// filename, print given
		args.startIndex = 0;
		args.endIndex = nPoints - 1;
		if ((argv[2] == string("true")) | (argv[2] == string("false")))
		{
			if (argv[2] == string("true"))
				args.printData = true;
			break;
		}
		args.improvementThreshold = parseArgumentThreshold(argv[2]);
		if (args.improvementThreshold < 0.0)
		{
			args.startIndex = -1;
		}
		break;
	}
	case 4:
	{
		// filename, start, end element or
		// filename, threshold, print
		args.startIndex = 0;
		args.endIndex = nPoints - 1;
		if ((argv[3] == string("true")) | (argv[3] == string("false")))
		{
			if (argv[3] == string("true"))
				args.printData = true;

			args.improvementThreshold = parseArgumentThreshold(argv[2]);
			if (args.improvementThreshold < 0.0)
			{
				args.startIndex = -1;
			}
			break;
		}

		args.startIndex = parseArgumentIndex(argv[2], csvData, nPoints);
		args.endIndex = parseArgumentIndex(argv[3], csvData, nPoints);
		args.improvementThreshold = defaultImprovementThreshold;
		if (args.endIndex == -1)
		{
			args.startIndex = -1;
		}
		break;
	}
	case 5:
	{
		// filename, start, end, threshold or
		// filename, start, end, print given
		if ((argv[4] == string("true")) | (argv[4] == string("false")))
		{
			if (argv[4] == string("true"))
				args.printData = true;
		}
		else
		{
			args.improvementThreshold = parseArgumentThreshold(argv[4]);
			if (args.improvementThreshold < 0.0)
			{
				args.startIndex = -1;
				break;
			}
		}
		args.startIndex = parseArgumentIndex(argv[2], csvData, nPoints);
		args.endIndex = parseArgumentIndex(argv[3], csvData, nPoints);
		if (args.endIndex == -1)
		{
			args.startIndex = -1;
		}
		break;
	}
	case 6:
	{
		// filename, start, end, threshold, print given
		args.startIndex = parseArgumentIndex(argv[2], csvData, nPoints);
		args.endIndex = parseArgumentIndex(argv[3], csvData, nPoints);
		if (args.endIndex == -1)
		{
			args.startIndex = -1;
		}
		args.improvementThreshold = parseArgumentThreshold(argv[4]);
		if (args.improvementThreshold < 0.0)
		{
			args.startIndex = -1;
		}
		if ((argv[5] == string("true")) | (argv[5] == string("false")))
		{
			if (argv[5] == string("true"))
				args.printData = true;
		}
		break;
	}
	}

	printArgs(args);
	if (args.startIndex == -1)
	{
		printf("Invalid parameters ...");
		exit(-1);
	}
	if (args.startIndex == args.endIndex)
	{
		printf("Start and end index (%d) cannot be the same ...", args.startIndex);
		exit(-1);
	}
	return args;
}

// set index to the front of the path (start point)
void setStartIndex(int index, Point* path)
{
	if (index == 0)
		return;
	Point tmpPoint;
	tmpPoint = path[0];
	path[0] = path[index];
	path[index] = tmpPoint;
}

// set index to the back of the path (end point)
void setEndIndex(int index, Point* path, int lastPoint)
{
	if (index == 0)
		return;
	Point tmpPoint;
	tmpPoint = path[lastPoint - 1];
	path[lastPoint-1] = path[index];
	path[index] = tmpPoint;
}