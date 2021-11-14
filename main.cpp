#include <iostream>
#include <string>
#include <sstream>
#include "tuple"
#include "meminfo.hpp"
#include "stat.hpp"
#include "uptime.hpp"

using namespace std;

void clearScreen();

int main(){

    string stat_filename_path = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\stat.txt";
    string line;
    string cpu_stat;
//    tuple cpu_stat_percentages;

//    while(true){
//        clearScreen();

        // cpu stats
        int number_of_cores = 0;
        ifstream stat_file(stat_filename_path);
        if(!stat_file.good()){
            cerr << "Could not open stat_file.... exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        while(getline(stat_file, line)){
            cpu_stat = get_cpu_stats(line);

            if (cpu_stat != "") {
                number_of_cores++;
                cpu_stat_percentages = get_cpu_percentages();
            }
        }
//    }


//    get_cpu_stats(stat_filename_path);
//
//
//    // absolute path of input dummy stat_file containing meminfo data
//    string meminfo_filename_path = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
//                           "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\meminfo.txt";
//
//    string free_memory, total_memory, buffers_memory, cached_memory;
//
//    total_memory = get_memory_stats(meminfo_filename_path, "MemTotal:");
//    free_memory = get_memory_stats(meminfo_filename_path, "MemFree:");
//    buffers_memory = get_memory_stats(meminfo_filename_path, "Buffers:");
//    cached_memory = get_memory_stats(meminfo_filename_path, "Cached:");
//
//
//    cout << "---------------------------------------------------------------------------------------------" << endl;
//    cout << "MEMORY     " << "Total: " << total_memory << endl;
//    cout << "           Free: " << free_memory << endl;
//    cout << "           Buffers: " << buffers_memory << endl;
//    cout << "           Cached: " << cached_memory << endl;
//    cout << "---------------------------------------------------------------------------------------------" << endl;
//
//    string uptime_filename_path = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
//                                "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\uptime.txt";
//
//
//    get_uptime(uptime_filename_path);
    return 0;
}

void clearScreen(){
    cout << "\033[2J\033[1;1H";
}