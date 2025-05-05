/*
header for args_handle.cpp
*/
#ifndef ARGS_HANDLE
#define ARGS_HANDLE

#include <bits/stdc++.h>
#include <vector>
#include <point.h>

using namespace std;

struct ArgParams
{
	int startIndex;
	int endIndex;
	float improvementThreshold;
	bool printData;
};

string getFileName(int argc, char *argv[]);
ArgParams setArgs();
ArgParams parseArgs(int argc, char *argv[], const vector<pair<string, vector<string>>> &csvData);
void setStartIndex(int index, vector<Point> &path);
void setEndIndex(int index, vector<Point> &path);

#endif // ARGS_HANDLE