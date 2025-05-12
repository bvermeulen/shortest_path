/*
header for args_handle.cpp
*/
#ifndef ARGS_HANDLE
#define ARGS_HANDLE

#include <bits/stdc++.h>
#include <point.h>
#include <../include_oo/csv.h>

using namespace std;

struct ArgParams
{
	int startIndex;
	int endIndex;
	int nPoints;
	float improvementThreshold;
	bool printData;
};

string getFileName(int argc, char *argv[]);
ArgParams parseArgs(int argc, char *argv[], Csv csv);
void setStartIndex(int index, Point* path);
void setEndIndex(int index, Point* path, int lenPath);

#endif // ARGS_HANDLE