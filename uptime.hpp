#include <string>
#include <vector>
#include <fstream>
#include <iostream>


using namespace std;

struct Sys_time{
    string up_time;
    string idle_time;
};

Sys_time get_up_idle_time(string, unsigned int);

string seconds_to_time(int);