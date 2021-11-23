#include <iostream>
#include <string>
#include "meminfo.hpp"
#include "stat.hpp"
#include "uptime.hpp"
#include <chrono>
#include <thread>

// TODO: if file cannot be opened, state the name of the file

// CLion-specific TODO: remove before submitting
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main(){

    // stat path
    string statPseudofilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\stat.txt";

    // meminfo path
    string meminfoPseudofilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                   "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\meminfo.txt";

    // uptime path
    string uptimePseudofilePath = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                  "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\uptime.txt";


    while(true) {

        // clears terminal
        system("cls"); // TODO: change command to "clear" before submitting

        // ----------------------------------------- STAT --------------------------------------------------------------

        vector<Core> allCores; // vector containing structs of type Core
        allCores = getCpuStats(statPseudofilePath); // populates vector with data about CPU cores
        unsigned short numberOfCores = allCores.size();

        // prints header
        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << "Total Core Cores: " << numberOfCores << endl;
        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << "Core" << setw(11) << "busy" << setw(11) << "idle" << setw(11) << "system" << setw(11) << "nice" << endl;

        // loops through vector and prints data about CPU cores
        for (Core core: allCores) {

            // parameters passed by reference, converted to percentages within function
            convertToPercent(core.busyTime, core.niceTime, core.systemTime, core.idleTime);

            cout << fixed;
            cout << setprecision(2);
            cout << core.name << setw(10) << core.busyTime << '%' << setw(10) << core.idleTime << '%' << setw(10)
                 << core.systemTime << '%' << setw(10) << core.niceTime << '%' << endl;
        }

        string pageInOutRatio = "N/A"; // values do not exist in pseudofile
        string swapInOutRatio = "N/A"; // values do not exist in pseudofile

        // gets data from stat about interrupts and context switches
        Quantity intrServ = formatCount(getInterruptsServiced(statPseudofilePath));
        Quantity ctxtSwitches = formatCount(getContextSwitchCount(statPseudofilePath));

        // prints data
        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << fixed << setprecision(2);
        cout << setw(10) << "Page in/out ratio: " << pageInOutRatio << " " << setw(35);
        cout << "Swap in/out ratio: " << swapInOutRatio << endl;
        cout << setw(10) << "Interrupts serviced: " << intrServ.number << " " << intrServ.multiplier;
        cout << setw(27) << "Context switch counts: " << ctxtSwitches.number << " " << ctxtSwitches.multiplier << endl;


        // ---------------------------------------- MEMINFO ------------------------------------------------------------
        string freeMemory, totalMemory, buffersMemory, cachedMemory;

        totalMemory = getMemoryStats(meminfoPseudofilePath, "MemTotal:");
        freeMemory = getMemoryStats(meminfoPseudofilePath, "MemFree:");
        buffersMemory = getMemoryStats(meminfoPseudofilePath, "Buffers:");
        cachedMemory = getMemoryStats(meminfoPseudofilePath, "Cached:");

        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;
        cout << "MEMORY" << setw(12) << "Total: " << kiloToMegabytes(totalMemory) << endl;
        cout << setw(17) << "Free: " << kiloToMegabytes(freeMemory) << endl;
        cout << setw(20) << "Buffers: " << kiloToMegabytes(buffersMemory) << endl;
        cout << setw(19) << "Cached: " << kiloToMegabytes(cachedMemory) << endl;
        cout << setw(80) << setfill('-') << '-' << setfill(' ') << endl;

        // ---------------------------------------- UPTIME -------------------------------------------------------------
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

        this_thread::sleep_for(std::chrono::milliseconds(500)); // pauses for 500 milliseconds

        break; //TODO: delete before submitting
    }
    return 0;
}
// CLion-specific TODO: remove before submitting
#pragma clang diagnostic pop