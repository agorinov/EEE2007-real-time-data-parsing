#include "uptime.hpp"

// Parse uptime file to extract the following data, in seconds:
//      up time: Wall clock since boot
//      idle time: combined idle time of all cpus
// Divide idle time by number of CPUs to obtain average idle time per Core
// return struct containing up time and average idle time as strings
UpIdleTime getUpIdleTime(string uptimePseudofilePath, unsigned int numberOfCores){

    ifstream uptimeFile(uptimePseudofilePath);

    if(!uptimeFile.is_open()){
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    float upTimeSecs = 0;
    float idleTimeSecs = 0;

    string token;
    bool obtainedSecondValue = false;
    // assigns first and second values in line to upTime and idleTime
    while(getline(uptimeFile, token, ' ')){
        if (obtainedSecondValue){
//            cout << "idleTime: "<< token << endl;
            idleTimeSecs = stof(token);
        } else {
//            cout << "upTime: "<< token << endl;
            upTimeSecs = stof(token);
            obtainedSecondValue = true;
        }
    }

//    cout << "upTimeSecs: " << upTimeSecs << endl;
    float upTime = upTimeSecs;
    float idleTime;
//  cout << "number of cores: " << numberOfCores << endl;
    if (numberOfCores != 0) { // validates number of cores
        idleTime = idleTimeSecs / (float) numberOfCores;// average idle time per Core
    } else {
        idleTime = -1; // forcing to -1 if invalid cpu information obtained
    }
//    cout << "idle time: " << idleTime << endl;
    uptimeFile.close();
    return UpIdleTime{upTime, idleTime};
}
// convert seconds to hours, minutes and second
// return string
string secondsToTime(unsigned int totalSeconds){

    unsigned short hours;
    unsigned short minutes;
    unsigned short seconds;

    hours = totalSeconds / 3600;
    minutes = (totalSeconds % 3600) / 60;
    seconds = (totalSeconds % 3600) % 60;

    return to_string(hours) + " hours " + to_string(minutes) + " minutes and " + to_string(seconds) + " seconds";
}
// calculate CPU's energy consumption given total time since boot and average cpu idle time
// assumes constant CPU active and idle power
// returns energy in Mega Joules
EnergyUsed calculateEnergyUsed(float timeSinceBoot, float idleTime){
    float activeEnergy;
    float idleEnergy;

    if (idleTime == -1){ // -1 indicates error
        activeEnergy = -1;
        idleEnergy = -1;
    } else {
//    cout << "timeSinceBoot: " << timeSinceBoot << endl;
//    cout << "idle time: " << idleTime << endl;
        float activeTime = timeSinceBoot - idleTime;
//    cout << "active time: " << activeTime << endl;

        float cpuActivePower = 60; // Watts
        float cpuIdlePower = 10; // Watts

        activeEnergy = cpuActivePower * activeTime / 1000000;
        idleEnergy = cpuIdlePower * idleTime / 1000000;

    }
    return EnergyUsed{activeEnergy, idleEnergy};
}
