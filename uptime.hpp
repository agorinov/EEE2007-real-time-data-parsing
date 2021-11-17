#include <string>
#include <vector>
#include <fstream>
#include <iostream>


using namespace std;

struct Sys_time{
    float up_time;
    float idle_time;
};

struct Energy_used{
    string active_energy;
    string idle_energy;
};

Sys_time get_up_idle_time(string, unsigned int);

string seconds_to_time(unsigned int);

Energy_used calculate_energy_used(float, float);