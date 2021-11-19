#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

using namespace std;

struct CPU // TODO: rename struct to "core"
{
    string name;
    float busy_time;
    float nice_time;
    float system_time;
    float idle_time;
};


vector<CPU> get_cpu_stats(string);

float *convert_to_percent(float, float, float, float);

string get_intr_serv(string);
