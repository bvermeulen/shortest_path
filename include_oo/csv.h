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

class Csv {
    
    public:
        Column *csvData;
        Csv();
        int getRows();
        int getCols();
        void write_csv(string filename);
        void read_csv(string filename);
        Point* createPath();
        void createCsvData(const Point* path, int lenPath);
        void printNodes(bool printData);
        Column* getCsvData();

    private:
        void initCsvData();
};

#endif // CSV_H
