#include <bits/stdc++.h>
#include <csv.h>
#include <point.h>

using namespace std;

void write_csv(string filename, const vector<pair<string, vector<string>>> &csvData)
{
    // Make a CSV file with one or more columns of integer values

    ofstream myFile(filename);

    // Send column names to the stream
    for (unsigned int i = 0; i < csvData.size(); ++i)
    {
        myFile << csvData[i].first;
        if (i != csvData.size() - 1)
            myFile << ",";
    }
    myFile << "\n";

    // Send data to the stream
    for (unsigned int i = 0; i < csvData[0].second.size(); ++i)
    {
        for (unsigned int j = 0; j < csvData.size(); ++j)
        {
            myFile << csvData[j].second[i];
            if (j != csvData.size() - 1)
                myFile << ",";
        }
        myFile << "\n";
    }
    myFile.close();
}

vector<pair<string, vector<string>>> read_csv(string filename)
{
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
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
            // Initialize and add <colname, string vector> pairs to result
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

// Create a path based on csv data
vector<Point> createPath(const vector<pair<string, vector<string>>> &csvData)
{
    vector<Point> path;
    for (unsigned int i = 0; i < csvData[0].second.size(); i++)
    {
        path.push_back(Point(csvData[0].second[i], stof(csvData[1].second[i]), stof(csvData[2].second[i])));
    }
    return path;
}

// Create csv data based on path and convert values to string with 1 decimal
vector<pair<string, vector<string>>> createCsvData(const vector<Point> &path)
{
    vector<string> id, x, y;
    ostringstream valStream;
    for (unsigned int i = 0; i < path.size(); i++)
    {
        id.push_back(path[i].id);
        valStream.str("");
        valStream << fixed << setprecision(1) << path[i].x;
        x.push_back(valStream.str());
        valStream.str("");
        valStream << fixed << setprecision(1) << path[i].y;
        y.push_back(valStream.str());
    }
    vector<pair<string, vector<string>>> csvData{{"label", id}, {"easting", x}, {"northing", y}};
    return csvData;
}

// Print the nodes
void printNodes(const vector<pair<string, vector<string>>> &csvData, bool printData)
{
    string h1 = csvData[0].first;
    string h2 = csvData[1].first;
    string h3 = csvData[2].first;
    printf("number of nodes: %3lu\n", csvData[0].second.size());
    if (!printData)
        return;
    for (unsigned int i = 0; i < csvData[0].second.size(); i++)
    {
        printf("%s: %s, %s: %.1f, %s: %.1f\n",
               h1.c_str(), csvData[0].second[i].c_str(), h2.c_str(),
               stof(csvData[1].second[i]), h3.c_str(), stof(csvData[2].second[i]));
    }
}
