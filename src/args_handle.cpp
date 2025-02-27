#include <bits/stdc++.h>
#include <args_handle.h>
#include <vector>
#include <point.h>

using namespace std;

float defaultImprovementThreshold = 0.001;

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

int parseArgumentIndex(string token, vector<pair<string, vector<string>>> &csvData)
{
	int value;
	int numberPoints = (int)csvData[0].second.size();
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

		if (value > numberPoints)
		{
			printf("Index %d must be less than %d\n", value, numberPoints);
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
		for (int i = 0; i < numberPoints; i++)
		{
			if (label == csvData[0].second[i])
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
		"threshold: %.4f\n",
		args.startIndex,
		args.endIndex,
		args.improvementThreshold);
}

ArgParams setArgs()
{
	ArgParams args;
	args.startIndex = 0;
	args.endIndex = 0;
	args.improvementThreshold = 0.001;
	printArgs(args);
	return args;
}

ArgParams parseArgs(int argc, char *argv[], vector<pair<string, vector<string>>> &csvData)
{
	ArgParams args;
	args.startIndex = -1;
	args.endIndex = -1;
	args.improvementThreshold = defaultImprovementThreshold;
	switch (argc)
	{
	case 1: // No input file
	{
		printf("No input file is given ...\n");
		break;
	}
	case 2: // only filename given
	{
		args.startIndex = 0;
		args.endIndex = 0;
		args.improvementThreshold = defaultImprovementThreshold;
		break;
	}
	case 3: // filename and threshold given
	{
		args.startIndex = 0;
		args.endIndex = 0;
		args.improvementThreshold = parseArgumentFloat(argv[2]);
		if (args.improvementThreshold < 0.0)
		{
			args.startIndex = -1;
		}
		break;
	}
	case 4: // filename, start and end element given
	{
		args.startIndex = parseArgumentIndex(argv[2], csvData);
		args.endIndex = parseArgumentIndex(argv[3], csvData);
		args.improvementThreshold = defaultImprovementThreshold;
		if (args.endIndex == -1)
		{
			args.startIndex = -1;
		}
		break;
	}
	case 5: // filename, start, end  and threshold given
	{
		args.startIndex = parseArgumentIndex(argv[2], csvData);
		args.endIndex = parseArgumentIndex(argv[3], csvData);
		if (args.endIndex == -1)
		{
			args.startIndex = -1;
		}
		args.improvementThreshold = parseArgumentFloat(argv[4]);
		if (args.improvementThreshold < 0.0)
		{
			args.startIndex = -1;
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
void setStartIndex(int index, vector<Point> &path)
{
	if (index == 0)
		return;
	Point tmpPoint;
	tmpPoint = path.front();
	path.front() = path[index];
	path[index] = tmpPoint;
}

// set index to the back of the path (end point)
void setEndIndex(int index, vector<Point> &path)
{
	if (index == 0)
		return;
	Point tmpPoint;
	tmpPoint = path.back();
	path.back() = path[index];
	path[index] = tmpPoint;
}