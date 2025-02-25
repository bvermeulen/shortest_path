/*
    Program to calculate the shortest time to traverse a set of nodes, whereby going straight is the
    fastest option.
    Command line arguments are:
        1 - file name of a csv file containing label, x, y of nodes (mandatory)
        2 - if value between 0 and 1 it is the threshold, otherwise is the element in the list
            where path must start (must be an integer >= 0) (optional)
        3 - threshold (must be between 0 and 1) (optional)

    start element default value is 0, threshold default value is 0.001

    @2024 howdiweb, bruno.vermeulen@hotmail.com
*/
#include <algorithm> // for reverse mapping
#include <math.h>
#include <vector>
#include <shortest_path_tsp.h>
#include <args_handle.h>
#include <csv.h>
#include <point.h>
#include <plotpaths.h>

using namespace std;

const float cruiseSpeed = 15.0, accelaration = 2, deceleration = 1, upDelay = 2, downDelay = 3;
const float instDelay = 0.0, sweep = 9.0;
const float angleDelay30 = 8, angleDelay60 = 6, angleDelay90 = 5, angleDelay120 = 3, angleDelay150 = 1, angleDelay180 = 0;

float angle3points(const Point p1, const Point p2, const Point p3)
{
    float angle;
    angle = rad_deg * (atan2(p3.y - p2.y, p3.x - p2.x) - atan2(p1.y - p2.y, p1.x - p2.x));
    if (angle < 0.0)
        angle += 360;
    if (angle > 180.0)
        angle = abs(angle - 360);
    return angle;
}

float calcDuration(const float distance, const float angle)
{
    float duration, angleDelay;
    if (angle < 30.0)
        angleDelay = angleDelay30;
    else if (angle < 60.0)
        angleDelay = angleDelay60;
    else if (angle < 90.0)
        angleDelay = angleDelay90;
    else if (angle < 120.0)
        angleDelay = angleDelay120;
    else if (angle < 150.0)
        angleDelay = angleDelay150;
    else
        angleDelay = angleDelay180;
    duration = downDelay + instDelay + sweep + upDelay + distance * 3.6 / cruiseSpeed + angleDelay;
    // printf("duration: %.2f", duration);
    return duration;
}

// Calculate the weighted path duration base on distance, angle and other delays
float WeightedPathDuration(vector<Point> &path)
{
    Point p1, p2, p3;
    float totalDuration = 0.0;
    float angle, distance, duration;
    for (unsigned int i = 0; i < path.size() - 2; i++)
    {
        p1 = path[i];
        p2 = path[(i + 1)];
        p3 = path[(i + 2)];
        if (i == 0)
        {
            distance = p1.dist(p2);
            duration = calcDuration(distance, 0.0);
            totalDuration += duration;
            // printf("i: %d, angle: %.1f, duration: %.1f, duration: %.1f\n", i, angle, distance, duration);
        }
        angle = angle3points(p1, p2, p3);
        distance = p2.dist(p3);
        duration = calcDuration(distance, angle);
        totalDuration += duration;
        // printf("i: %d, angle: %.1f, distance: %.1f, duration: %.1f, total: %.0f\n", i, angle, distance, duration, totalDuration);
    }
    return totalDuration;
}

// Perform a 2-opt swap
void do2Opt(vector<Point> &path, int i, int j)
{
    reverse(begin(path) + i + 1, begin(path) + j + 1);
}

int main(int argc, char *argv[])
{
    PlotPaths myPlt;
    ArgParams args = parseArgs(argc, argv);
    // ArgParams args = setArgs();

    string csvFile = args.fileName;
    unsigned int startElement = (unsigned int)args.startElement;
    unsigned int endElement = (unsigned int)args.endElement;
    float improvementThreshold = args.improvementThreshold;
    vector<pair<string, vector<string>>> csvData = read_csv(csvFile);
    printNodes(csvData, false);
    vector<Point> path = createPath(csvData);
    // swap first element to desired start point
    if ((startElement > path.size()) | (endElement > path.size()))
    {
        printf("Swap elemensts %d, %d must be less than %llu", startElement, endElement, path.size());
        return -1;
    }
    swapStartElement(startElement, path);
    swapEndElement(endElement, path);

    int n = path.size();
    vector<Point> newPath;
    float bestDistance = WeightedPathDuration(path);
    float newDistance, distanceToBeat;
    float improvementFactor = 1.0;

    printf("\nbest distance: %.0f, improvement factor: %.6f", bestDistance, improvementFactor);
    myPlt.plotFullPath(path);
    myPlt.Save();
    myPlt.Blit(2);

    // start and end point are fixed: for (j = i + 1; j < n - 1; j++)
    while (improvementFactor > improvementThreshold)
    {
        distanceToBeat = bestDistance;
        for (int i = 0; i < n - 2; i++)
        {
            for (int j = i + 1; j < n - 1; j++)
            {
                newPath = path;
                do2Opt(newPath, i, j);
                newDistance = WeightedPathDuration(newPath);
                if (newDistance < bestDistance)
                {
                    path = newPath;
                    bestDistance = newDistance;
                }
            }
        }
        improvementFactor = 1.0 - bestDistance / distanceToBeat;
        printf("\nbest distance: %.0f, improvement factor: %.6f", bestDistance, improvementFactor);
        myPlt.plotFullPath(path);
        myPlt.Save();
        myPlt.Blit(2);
    }
    printf("\n\n");
    myPlt.plotFullPath(path);
    myPlt.Save();
    myPlt.Show();
    vector<pair<string, vector<string>>> csvOutData = createCsvData(path);
    printNodes(csvOutData, false);
    string const csvOutFile = csvFile.substr(0, csvFile.find_last_of(".csv") - 3) + "_solution.csv";
    write_csv(csvOutFile, csvOutData);
    return 0;
}
