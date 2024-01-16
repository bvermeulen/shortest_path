#include "csv.h"
#include <fstream>

using namespace std;

void write_csv(string filename, vector<pair<string, vector<string>>> dataset)
{
    // Make a CSV file with one or more columns of integer values

    ofstream myFile(filename);

    // Send column names to the stream
    for (unsigned int i = 0; i < dataset.size(); ++i)
    {
        myFile << dataset[i].first;
        if (i != dataset.size() - 1)
            myFile << ",";
    }
    myFile << "\n";

    // Send data to the stream
    for (unsigned int i = 0; i < dataset[0].second.size(); ++i)
    {
        for (unsigned int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset[j].second[i];
            if (j != dataset.size() - 1)
                myFile << ",";
        }
        myFile << "\n";
    }
    myFile.close();
}

vector<pair<string, vector<string>>> read_csv(string filename)
{
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    vector<pair<string, vector<string>>> result;
    ifstream myFile(filename);
    if (!myFile)
    {
        printf("File %s: ", filename.c_str());
        throw runtime_error("File does not exist ...");
    }
    string line, colname;
    string val, token;
    if (myFile.good())
    {
        getline(myFile, line);
        stringstream ss(line);

        // Extract each column name
        while (getline(ss, colname, ','))
        {
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, vector<string>{}});
        }

        // Read data, line by line
        while (getline(myFile, line))
        {
            stringstream ss(line);
            int colIdx = 0;
            while (getline(ss, token, ','))
            {
                // Add the current integer to the colIdx columns values vector
                result[colIdx].second.push_back(token);
                // if (ss.peek() == ',') ss.ignore();
                colIdx++;
            }
        }
    }
    myFile.close();
    return result;
}
