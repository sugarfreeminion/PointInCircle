/*************************************************************************
 *  Author:         sugarfreeoh
 *  Date:           12 March 2016
 *  Description:    Having coordinates of the center of a circle, its
 *                  radius, and coordinates of a point you need to define
 *                  whether this point is located inside of this circle
 *************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

struct coordinate
{
    float x;
    float y;
};

struct circle
{
    coordinate center;
    float radius;
};

void ParseCoordinateString(string coordString, coordinate &coord);
void ParseRadiusString(string radiusString, float &radius);
void ParseCoordinate(string coord, coordinate &c);

bool IsPointInCircle(circle c, coordinate point);

int main(int argc, char *argv[])
{
    ifstream inputFile;

    inputFile.open(argv[1]);

    if(inputFile.is_open())
    {
        string line;
        string centerString;
        string radiusString;
        string pointString;

        circle c;
        coordinate point;

        while(getline(inputFile,line))
        {
            stringstream ss;
            size_t delLocation;
            size_t tempLoc;

            //cout << line << endl;

            delLocation = line.find(';');
            centerString = line.substr(0,delLocation);
            
            tempLoc = delLocation;

            delLocation = line.find(';',delLocation+2);
            radiusString = line.substr(tempLoc+2,delLocation-tempLoc-2);

            pointString = line.substr(delLocation+2);

            //cout << "CenterString: " << centerString << endl;
            //cout << "RadiusString: " << radiusString << endl;
            //cout << "PointString: " << pointString << endl;

            ParseCoordinateString(centerString, c.center);
            //cout << "Center of Circle: " << c.center.x << "," << c.center.y << endl;

            ParseRadiusString(radiusString, c.radius);
            //cout << "Radius of Circle: " << c.radius << endl;

            ParseCoordinateString(pointString, point);
            //cout << "Point of interest: " << point.x << "," << point.y << endl;

            if(IsPointInCircle(c,point))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }

    }
    else
    {
        cout << "Error opening input file" << endl;
    }

    return 0;
}

bool IsPointInCircle(circle c, coordinate point)
{
    bool isPointInCircle = false;

    float d;
    float xDist;
    float yDist;

    xDist = (c.center.x - point.x);
    yDist = (c.center.y - point.y);

    d = sqrt(pow(xDist,2) + pow(yDist,2));

    if(d <= c.radius)
        isPointInCircle = true;
    else
        isPointInCircle = false;

    return isPointInCircle;
}

void ParseCoordinateString(string coordString, coordinate &coord)
{
    size_t delLocation;
    string temp;

    delLocation = coordString.find('(');

    temp = coordString.substr(delLocation+1);

    ParseCoordinate(temp, coord);
}

void ParseRadiusString(string radiusString, float &radius)
{
    size_t delLocation;
    stringstream ss;
    string temp;

    delLocation = radiusString.find(':');

    temp = radiusString.substr(delLocation+1);

    ss << temp;
    ss >> radius;
}

void ParseCoordinate(string coord, coordinate &c)
{
    stringstream ss;
    string temp;

    size_t delLocation;

    delLocation = coord.find(',');

    temp = coord.substr(0,delLocation);

    ss << temp;
    ss >> c.x;

    temp = coord.substr(delLocation+2,coord.size()-temp.size()-3);

    ss.str("");
    ss.clear();

    ss << temp;
    ss >> c.y;
}
