#include <string>
#include <vector>
#include <fstream>
#include <iostream>


using namespace std;

struct UpIdleTime{
    float upTime;
    float idleTime;
};

struct EnergyUsed{
    float activeEnergy;
    float idleEnergy;
};

UpIdleTime getUpIdleTime(string uptimePseudofilePath, unsigned int numberOfCores);

string secondsToTime(unsigned int);

EnergyUsed calculateEnergyUsed(float, float);