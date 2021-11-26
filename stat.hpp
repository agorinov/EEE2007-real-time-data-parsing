#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

using namespace std;

struct Core
{
    string name;
    float busyTime;
    float niceTime;
    float systemTime;
    float idleTime;
};

struct Quantity
{
    float number;
    string multiplier;
};


vector<Core> getCpuStats(string filename);

void convertToPercent(float&, float&, float&, float&);

string getInterruptsServiced(string filename);

string getContextSwitchCount(string filename);

Quantity formatCount(string count);

string getSwapRatio(string);

string getPageRatio(string filename);
