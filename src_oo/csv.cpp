#include <bits/stdc++.h>
#include <../include_oo/csv.h>
#include <../include_oo/point.h>

using namespace std;

Csv::Csv() {
    csvData = new Column[numberCols];
}

void Csv::initCsvData()
{
    for (int i = 0; i < numberCols; i++)
    {
        csvData[i].colName = "@";
    }

    for (int i = 0; i < numberCols; i++)
    {
        for (int j = 0; j < numberRows; j++)
        {
            csvData[i].colValues[j] = "@";
        }
    }
}

int Csv::getRows()
{
    int numRows = 0;
    for (int i = 0; i < numberRows; i++)
    {
        if (csvData[0].colValues[i] == "@")
            break;
        numRows++;
    }
    return numRows;
}

int Csv::getCols()
{
    int numCols = 0;
    for (int i = 0; i < numberCols; i++)
    {
        if (csvData[i].colName == "@")
            break;
        numCols++;
    }
    return numCols;
}

int Csv::getLabelIndex(string label)
{
    int nPoints = getRows();
    for (int i = 0; i < nPoints; i++)
    {
        if (label == csvData[0].colValues[i])
        {
            return i;
        }
    }
    return -1;
}

void Csv::write_csv(string filename)
{
    // Make a CSV file with one or more columns of integer values

    int numRows = getRows();
    int numCols = getCols();

    ofstream myFile(filename);
    // Send column names to the stream
    for (int i = 0; i < numCols; ++i)
    {
        myFile << csvData[i].colName;
        if (i != numCols - 1)
            myFile << ",";
    }
    myFile << "\n";

    // Send data to the stream
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            myFile << csvData[j].colValues[i];
            if (j != numCols - 1)
                myFile << ",";
        }
        myFile << "\n";
    }
    myFile.close();
}

void Csv::read_csv(string filename)
{
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
    // each pair represents <column name, column values>
    initCsvData();
    ifstream myFile(filename);
    if (!myFile)
    {
        printf("File %s: ", filename.c_str());
        throw runtime_error("File does not exist ...");
    }
    string line, colName;
    string val, colValue;
    if (myFile.good())
    {
        getline(myFile, line);
        stringstream ss(line);

        int colIdx = 0;
        while (getline(ss, colName, ','))
        {
            csvData[colIdx].colName = colName;
            colIdx++;
        }

        int rowIdx = 0;
        while (getline(myFile, line))
        {
            stringstream ss(line);
            colIdx = 0;
            while (getline(ss, colValue, ','))
            {
                // add the values for the columns for this line
                csvData[colIdx].colValues[rowIdx] = colValue;
                colIdx++;
            }
            rowIdx++;
        }
    }
    myFile.close();
}

// Create a path based on csv data
void Csv::fillPath(Point *path)
{
    int numRows = getRows();

    for (int i = 0; i < numRows; i++)
    {
        path[i] = Point(
            csvData[0].colValues[i],
            stof(csvData[1].colValues[i]),
            stof(csvData[2].colValues[i]));
    }
}

// Create csv data based on path and convert values to string with 1 decimal
void Csv::createCsvData(const Point* path, int lenPath)
{
    ostringstream valStream;
    initCsvData();

    csvData[0].colName = "label";
    csvData[1].colName = "easting";
    csvData[2].colName = "northing";

    for (int i = 0; i < lenPath; i++)
    {
        csvData[0].colValues[i] = path[i].id;

        valStream.str("");
        valStream << fixed << setprecision(1) << path[i].x;
        csvData[1].colValues[i] = valStream.str();

        valStream.str("");
        valStream << fixed << setprecision(1) << path[i].y;
        csvData[2].colValues[i] = valStream.str();
    }
}

// Print the nodes in text format
void Csv::printNodesTxt(bool printData)
{
    int numRows = getRows();

    if (!printData)
        return;

    for (int i = 0; i < numRows; i++)
    {
        printf("%-s: %8s, %-s: %9.1f, %-s: %9.1f\n",
               csvData[0].colName.c_str(),
               csvData[0].colValues[i].c_str(),
               csvData[1].colName.c_str(),
               stof(csvData[1].colValues[i]),
               csvData[2].colName.c_str(),
               stof(csvData[2].colValues[i]));
    }
}

// Print the nodes in csv format
void Csv::printNodesCsv(bool printData)
{
    int numRows = getRows();

    if (!printData)
        return;

    printf("%10s, %10s, %10s\n",
           csvData[0].colName.c_str(),
           csvData[1].colName.c_str(),
           csvData[2].colName.c_str());

    for (int i = 0; i < numRows; i++)
    {
        printf("%10s, %10.1f, %10.1f\n",
               csvData[0].colValues[i].c_str(),
               stof(csvData[1].colValues[i]),
               stof(csvData[2].colValues[i]));
    }
}
