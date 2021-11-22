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

//    getline(uptimeFile, line);
//
//    // split space-delimited line into two values
//    string space_delimiter = " ";
//    size_t pos = 0;
//    pos = line.find(space_delimiter);
//    upTimeSecs = stof(line.substr(0, pos));
//    line.erase(0, pos + space_delimiter.length());
//    idleTimeSecs = stof(line);


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
    float idleTime = idleTimeSecs / numberOfCores; // average idle time per Core

//    cout << "idle time: " << idleTime << endl;
    uptimeFile.close();
    return UpIdleTime{upTime, idleTime};
}

string secondsToTime(unsigned int totalSeconds){

    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

    hours = totalSeconds / 3600;
    minutes = (totalSeconds % 3600) / 60;
    seconds = (totalSeconds % 3600) % 60;

    return to_string(hours) + " hours " + to_string(minutes) + " minutes and " + to_string(seconds) + " seconds";
}

EnergyUsed calculateEnergyUsed(float timeSinceBoot, float idleTime){

//    cout << "timeSinceBoot: " << timeSinceBoot << endl;
//    cout << "idle time: " << idleTime << endl;
    float activeTime = timeSinceBoot - idleTime;
//    cout << "active time: " << activeTime << endl;

    float cpuActivePower = 60; // Watts
    float cpuIdlePower = 10; // Watts

    float activeEnergy = cpuActivePower * activeTime / 1000000;
    float idleEnergy = cpuIdlePower * idleTime / 1000000;

    return EnergyUsed{activeEnergy, idleEnergy};
}
