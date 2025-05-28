/*
    Program to calculate the shortest time to traverse a set of nodes, whereby going straight is the
    fastest option.
    Command line argument number:
        1 - file name of a csv file containing label, x, y of nodes (mandatory)
        2 - file name, threshold value (must be a value between 0 and 1) (optional)
          - file name, print (bool true or false)
        3 - file name, start point, end point
                if the start or end points are an integer they represent the index
                if the start or end points start with "L", then it is the label
          - file name, threshold, print
        4 - file name, start point, end point, threshold
          - file name, start point, end point, print
        5 - file name, start point, end point, threshold, print

        Default values: start point: index 0; end point: last index; threshold: 0.001

    @2025 howdiweb, bruno.vermeulen@hotmail.com
*/
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <shortest_path_tsp.h>
#include <args_handle.h>
#include <csv.h>
#include <point.h>
#include <plotpaths.h>

using namespace std;


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
float WeightedPathDuration(const Point *path, int nPoints)
{
    Point p1, p2, p3;
    float totalDuration = 0.0;
    float angle, distance, duration;
    for (int i = 0; i < nPoints - 1; i++)
    {
        p2 = path[(i)];
        p3 = path[(i + 1)];
        if (i == 0)
        {
            angle = 0.0;
        }
        else
        {
            p1 = path[i - 1];
            angle = angle3points(p1, p2, p3);
        }
        distance = p2.dist(p3);
        duration = calcDuration(distance, angle);
        totalDuration += duration;
    }
    return totalDuration;
}

// Perform a 2-opt swap
void do2Opt_1(Point *path, int r1, int r2)
{
    assert(r2 > r1);
    Point tmpPoint;
    for (int i = 0; i < (r2 - r1) / 2; i++)
    {
        tmpPoint = path[r1 + i + 1];
        path[r1 + i + 1] = path[r2 - i];
        path[r2 - i] = tmpPoint;
    }
}

void do2Opt(Point *path, int r1, int r2)
{
    reverse(path + r1 + 1, path + r2 + 1);
}

int main(int argc, char *argv[])
{
    py::scoped_interpreter guard{};
    py::module site = py::module::import("site");
    site.attr("addsitedir")(sitePackages);

    PlotPaths myPlt = PlotPaths();
    string csvFile = getFileName(argc, argv);
    Column *csvData = read_csv(csvFile);
    ArgParams args = parseArgs(argc, argv, csvData);
    // ArgParams args = setArgs();
    Point *path = createPath(csvData);

    int startIndex = args.startIndex;
    int endIndex = args.endIndex;
    float improvementThreshold = args.improvementThreshold;
    printNodes(csvData, args.printData);
    // set the index for start point and end point
    int n = args.nPoints;
    setStartIndex(startIndex, path);
    setEndIndex(endIndex, path, n);

    Point *newPath;
    newPath = new Point[n];
    float bestDistance = WeightedPathDuration(path, n);
    float newDistance, distanceToBeat;
    float improvementFactor = 1.0;

    printf("\nbest distance: %.0f, improvement factor: %.6f", bestDistance, improvementFactor);
    myPlt.plotFullPath(path, n);
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
                copy(path, path + n, newPath);
                do2Opt(newPath, i, j);
                newDistance = WeightedPathDuration(newPath, n);
                if (newDistance < bestDistance)
                {
                    copy(newPath, newPath + n, path);
                    bestDistance = newDistance;
                }
            }
        }
        improvementFactor = 1.0 - bestDistance / distanceToBeat;
        printf("\nbest distance: %.0f, improvement factor: %.6f", bestDistance, improvementFactor);
        myPlt.plotFullPath(path, n);
        myPlt.Save();
        myPlt.Blit(2);
    }
    printf("\n\n");
    myPlt.plotFullPath(path, n);
    myPlt.Save();
    myPlt.Show();
    Column *csvOutData = createCsvData(path, n);
    printNodes(csvOutData, args.printData);
    string const csvOutFile = csvFile.substr(0, csvFile.find_last_of(".csv") - 3) + "_solution.csv";
    write_csv(csvOutFile, csvOutData);
    printf("The program is finished ...\n");
}
