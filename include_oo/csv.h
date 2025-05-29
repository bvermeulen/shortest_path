#ifndef CSV_H
#define CSV_H

#include <point.h>

using namespace std;

class Csv
{

    private:
        static const int numberCols = 3;
        static const int numberRows = 2000;
    
        struct Column
        {
            string colName;
            string colValues[numberRows];
        };
        Column *csvData;
        void initCsvData();

    public:
        Csv();
        int getRows();
        int getCols();
        void write_csv(string filename);
        void read_csv(string filename);
        int getLabelIndex(string label);
        void fillPath(Point *path);
        void createCsvData(const Point *path, int lenPath);
        void printNodesTxt(bool printData);
        void printNodesCsv(bool printData);
};

#endif // CSV_H
