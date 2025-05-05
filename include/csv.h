#ifndef CSV_H
#define CSV_H

#include <vector>
#include <point.h>

using namespace std;

void write_csv(string filename, const vector<pair<string, vector<string>>> &csvData);
vector<pair<string, vector<string>>> read_csv(string filename);
vector<Point> createPath(const vector<pair<string, vector<string>>> &csvData);
vector<pair<string, vector<string>>> createCsvData(const vector<Point> &path);
void printNodes(const vector<pair<string, vector<string>>> &csvData, bool printData);

#endif // CSV_H
