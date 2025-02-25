/*
header for args_handle.cpp
*/
#ifndef ARGS_HANDLE
#define ARGS_HANDLE
#include <sstream>
#include <vector>
#include <point.h>

using namespace std;

struct ArgParams
{
	string fileName;
	int startElement;
	int endElement;
	float improvementThreshold;
};

ArgParams setArgs();
ArgParams parseArgs(int argc, char *argv[]);
void swapStartElement(int index, vector<Point> &path);
void swapEndElement(int index, vector<Point> &path);

#endif // ARGS_HANDLE