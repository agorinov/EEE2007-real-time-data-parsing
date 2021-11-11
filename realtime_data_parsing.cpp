#include <fstream>
#include <iostream>
#include <string>
#include "Memory.hpp"

using namespace std;

int main(){
    // absolute path of input dummy file containing meminfo data
    ifstream meminfo_file("C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                    "Computer Systems and Microprocessors\\projects\\realtime_data_parsing\\meminfo.txt");

    if(!meminfo_file.is_open()){
        cerr << "Output file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string free_memory, total_memory, buffers_memory, cached_memory;

    while (getline(meminfo_file, line)){

        free_memory = get_memory_stat(line, "MemFree:");
        total_memory = get_memory_stat(line, "MemTotal:");
        buffers_memory = get_memory_stat(line, "Buffers:");
        cached_memory = get_memory_stat(line, "Cached:");

    }

    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "MEMORY     " << "Total: " << total_memory << endl;
    cout << "           Free: " << free_memory << endl;
    cout << "           Buffers: " << buffers_memory << endl;
    cout << "           Cached: " << cached_memory << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;

    meminfo_file.close();

    return 0;
}