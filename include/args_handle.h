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
	int startElement;
	int endElement;
	float improvementThreshold;
};

string getFileName(int argc, char *argv[]);
ArgParams setArgs();
ArgParams parseArgs(int argc, char *argv[], vector<pair<string, vector<string>>> &csvData);
void swapStartElement(int index, vector<Point> &path);
void swapEndElement(int index, vector<Point> &path);

#endif // ARGS_HANDLE