#ifndef CSV_H
#define CSV_H

#include <vector>
#include <sstream>

using namespace std;

void write_csv(string filename, vector<pair<string, vector<string>>> dataset);
vector<pair<string, vector<string>>> read_csv(string filename);

#endif
