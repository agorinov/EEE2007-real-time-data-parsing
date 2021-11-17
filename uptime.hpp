#include <string>
#include <vector>
#include <fstream>
#include <iostream>


using namespace std;

struct Sys_time{
    string up_time;
    string idle_time;
};

struct Energy_used{
    string active_energy;
    string idle_energy;
};

Sys_time get_up_idle_time(string, unsigned int);

string seconds_to_time(int);

Energy_used calculate_energy_used(unsigned int, unsigned int);