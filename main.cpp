#include <iostream>
#include <string>
#include "meminfo.hpp"
#include "stat.hpp"
#include "uptime.hpp"
#include <chrono>
#include <thread>

// TODO: optimize data types before submission eg: short vs long vs unsigned int, etc
// TODO: if file cannot be opened, state the name of the file

// CLion-specific TODO: remove before submitting
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main(){

    while(true) {
        system("cls"); // TODO: change command to "clear" before submitting

        string statPseudofilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                    "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\stat.txt";

        vector<Core> allCores; // vector containing structs of type Core
        allCores = getCpuStats(statPseudofilePath);
        unsigned short numberOfCores = allCores.size();

        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << "Total Core Cores: " << numberOfCores << endl;
        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << "Core" << setw(10) << "busy" << setw(12) << "idle" << setw(13) << "system" << setw(10) << "nice" << endl;

        float *cpuPercent;
        for (Core core: allCores) {

            cpuPercent = convertToPercent(core.busyTime, core.niceTime, core.systemTime, core.idleTime);

            cout << fixed;
            cout << setprecision(2);
            cout << core.name << setw(10) << cpuPercent[0] << '%' << setw(10) << cpuPercent[3] << '%' << setw(10)
                 << cpuPercent[2] << '%' << setw(10) << cpuPercent[1] << '%' << endl;

        }
        //    delete[] cpuPercent; //TODO: find out if array memory needs to be freed

        string pageInOutRatio = "N/A";
        string swapInOutRatio = "N/A";
        Quantity interruptsServiced = formatCount(getInterruptsServiced(statPseudofilePath));
        Quantity contextSwitchCounts = formatCount(getContextSwitchCount(statPseudofilePath));

        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << fixed << setprecision(2);
        cout << setw(10) << "Page in/out ratio: " << pageInOutRatio << " " << setw(35) << "Swap in/out ratio: " << swapInOutRatio << endl;
        cout << setw(10) << "Interrupts serviced: " << interruptsServiced.number << " " << interruptsServiced.multiplier;
        cout << setw(27) << "Context switch counts: " << contextSwitchCounts.number << " " << contextSwitchCounts.multiplier << endl;


        // absolute path of input dummy file containing meminfo data
        string meminfoPseudofilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                       "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\meminfo.txt";

        string freeMemory, totalMemory, buffersMemory, cachedMemory;

        totalMemory = getMemoryStats(meminfoPseudofilePath, "MemTotal:");
        freeMemory = getMemoryStats(meminfoPseudofilePath, "MemFree:");
        buffersMemory = getMemoryStats(meminfoPseudofilePath, "Buffers:");
        cachedMemory = getMemoryStats(meminfoPseudofilePath, "Cached:");


        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << "MEMORY" << setw(12) << "Total: " << totalMemory << endl;
        cout << setw(17) << "Free: " << freeMemory << endl;
        cout << setw(20) << "Buffers: " << buffersMemory << endl;
        cout << setw(19) << "Cached: " << cachedMemory << endl;
        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;

        string uptimePseudofilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                      "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\uptime.txt";


        UpIdleTime upIdleTime = getUpIdleTime(uptimePseudofilePath, numberOfCores);

        string upTime = secondsToTime(upIdleTime.upTime);
        string idleTime = secondsToTime(upIdleTime.idleTime); // average idle time per Core

        cout << "SYSTEM" << setw(12) << "UP for " << upTime << endl;
        cout << setw(20) << "IDLE for " << idleTime << endl;

//        cout << "timeSinceBoot: " << upIdleTime.upTime << endl;
//        cout << "idle time: " << upIdleTime.idleTime << endl;

        EnergyUsed energyUsed = calculateEnergyUsed(upIdleTime.upTime, upIdleTime.idleTime);

        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << "ENERGY" << endl;
        cout << fixed << setprecision(2);
        cout << setw(28) << "In Active State: " << energyUsed.activeEnergy << " MJoules" << endl;
        cout << setw(26) << "In Idle State: " << energyUsed.idleEnergy << " MJoules" << endl;
        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;




        this_thread::sleep_for(std::chrono::milliseconds(500));

        break; //TODO: delete before submitting

    }

    return 0;
}


// CLion-specific TODO: remove before submitting
#pragma clang diagnostic pop