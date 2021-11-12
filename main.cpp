#include <iostream>
#include <string>
#include "meminfo.hpp"
#include "stat.hpp"

using namespace std;

int main(){
    // absolute path of input dummy file containing meminfo data
    string meminfo_filename_path = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                           "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\meminfo.txt";

    string free_memory, total_memory, buffers_memory, cached_memory;

    total_memory = get_memory_stats(meminfo_filename_path, "MemTotal:");
    free_memory = get_memory_stats(meminfo_filename_path, "MemFree:");
    buffers_memory = get_memory_stats(meminfo_filename_path, "Buffers:");
    cached_memory = get_memory_stats(meminfo_filename_path, "Cached:");


    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "MEMORY     " << "Total: " << total_memory << endl;
    cout << "           Free: " << free_memory << endl;
    cout << "           Buffers: " << buffers_memory << endl;
    cout << "           Cached: " << cached_memory << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;


    string stat_filename_path = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                                "Computer Systems and Microprocessors\\projects\\realtime_data_parsing3\\stat.txt)";

    get_cpu_stats(stat_filename_path);


    return 0;
}