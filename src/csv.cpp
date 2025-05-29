#include <bits/stdc++.h>
#include <csv.h>
#include <point.h>

using namespace std;

void initCsvData(Column *csvData)
{
    for (int i = 0; i < numberCols; i++)
    {
        csvData[i].colName = "@";
        for (int j = 0; j < numberRows; j++)
        {
            csvData[i].colValues[j] = "@";
        }
    }
}

int getRows(const Column *csvData)
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

int getCols(const Column *csvData)
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

void write_csv(string filename, const Column *csvData)
{
    // Make a CSV file with one or more columns of integer values

    int numRows = getRows(csvData);
    int numCols = getCols(csvData);

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

Column *read_csv(string filename)
{
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
    // each pair represents <column name, column values>
    Column *csvData;
    csvData = new Column[numberCols];
    initCsvData(csvData);
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
    return csvData;
}

// Create a path based on csv data
Point* createPath(const Column *csvData)
{
    int numRows = getRows(csvData);
    Point* path;
    path = new Point[numRows];

    for (int i = 0; i < numRows; i++)
    {
        path[i] = Point(
            csvData[0].colValues[i],
            stof(csvData[1].colValues[i]),
            stof(csvData[2].colValues[i]));
    }
    return path;
}

// Create csv data based on path and convert values to string with 1 decimal
Column *createCsvData(const Point* path, int lenPath)
{
    ostringstream valStream;
    Column *csvData;
    csvData = new Column[numberCols];
    initCsvData(csvData);

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
    return csvData;
}

// Print the nodes
void printNodes(const Column *csvData, bool printData)
{
    int numRows = getRows(csvData);

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
