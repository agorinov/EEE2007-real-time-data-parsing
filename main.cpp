#include <iostream>
#include <string>
#include "meminfo.hpp"
#include "stat.hpp"
#include "uptime.hpp"
#include <chrono>
#include <thread>

// TODO: optimize data types before submission eg: short vs long vs unsigned int, etc
// TODO:

// CLion-specific TODO: remove before submitting
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

void clearScreen();

int main(){

    while(true) {
//        clearScreen();
        system("cls");

        string stat_filename_path = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                    "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\stat.txt";

        vector<CPU> all_CPUs; // vector containing structs of type CPU
        all_CPUs = get_cpu_stats(stat_filename_path);
        unsigned int number_of_CPUs = all_CPUs.size();

        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << "Total CPU Cores: " << number_of_CPUs << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << "CPU" << setw(10) << "busy" << setw(12) << "idle" << setw(13) << "system" << setw(10) << "nice" << endl;

        float *cpu_perc;
        for (CPU cpu: all_CPUs) {

            cpu_perc = convert_to_percent(cpu.busy_time, cpu.nice_time, cpu.system_time, cpu.idle_time);

            cout << fixed;
            cout << setprecision(2);
            cout << cpu.name << setw(10) << cpu_perc[0] << '%' << setw(10) << cpu_perc[3] << '%' << setw(10)
                 << cpu_perc[2] << '%' << setw(10) << cpu_perc[1] << '%' << endl;

        }
        //    delete[] cpu_perc; //TODO: find out if array memory needs to be freed





        // absolute path of input dummy file containing meminfo data
        string meminfo_filename_path = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                       "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\meminfo.txt";

        string free_memory, total_memory, buffers_memory, cached_memory;

        total_memory = get_memory_stats(meminfo_filename_path, "MemTotal:");
        free_memory = get_memory_stats(meminfo_filename_path, "MemFree:");
        buffers_memory = get_memory_stats(meminfo_filename_path, "Buffers:");
        cached_memory = get_memory_stats(meminfo_filename_path, "Cached:");


        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << "MEMORY" << setw(12) << "Total: " << total_memory << endl;
        cout << setw(17) << "Free: " << free_memory << endl;
        cout << setw(20) << "Buffers: " << buffers_memory << endl;
        cout << setw(19) << "Cached: " << cached_memory << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;

        string uptime_filename_path = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                      "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\uptime.txt";


        Sys_time sys_time = get_up_idle_time(uptime_filename_path, number_of_CPUs);

        cout << "SYSTEM" << setw(39) << sys_time.up_time << endl;
        cout << setw(44)  << sys_time.idle_time << endl;

        // TODO: print energy consumption



        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        break; //TODO: delete before submitting

    }

    return 0;
}

void clearScreen(){
    cout << "\033[2J\033[1;1H";
}

// CLion-specific TODO: remove before submitting
#pragma clang diagnostic pop