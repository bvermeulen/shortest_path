#ifndef CSV_H
#define CSV_H

#include <vector>
#include <sstream>
#include <point.h>

using namespace std;

void write_csv(string filename, vector<pair<string, vector<string>>> dataset);
vector<pair<string, vector<string>>> read_csv(string filename);
vector<Point> createPath(vector<pair<string, vector<string>>> &csvData);
vector<pair<string, vector<string>>> createCsvData(vector<Point> &path);
void printNodes(vector<pair<string, vector<string>>> &csvData, bool printData);

#endif // CSV_H
