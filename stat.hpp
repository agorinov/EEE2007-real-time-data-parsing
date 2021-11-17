#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

using namespace std;

struct CPU
{
    string name;
    float busy_time;
    float nice_time;
    float system_time;
    float idle_time;
};

struct Energy_used{
    string active_energy;
    string idle_energy;
};

vector<CPU> get_cpu_stats(string);

float *convert_to_percent(float, float, float, float);

Energy_used calculate_energy_used(unsigned int, unsigned int);