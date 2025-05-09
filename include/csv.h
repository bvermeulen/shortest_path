#ifndef CSV_H
#define CSV_H

#include <point.h>

using namespace std;

const int numberCols = 3;
const int numberRows = 2000;

struct Column
{
    string colName;
    string colValues[numberRows];
};

int getRows(const Column *csvData);
int getCols(const Column *csvData);
void write_csv(string filename, const Column *csvData);
Column *read_csv(string filename);
Point* createPath(const Column *csvData);
Column* createCsvData(const Point* path, int lenPath);
void printNodes(const Column *csvData, bool printData);

#endif // CSV_H
