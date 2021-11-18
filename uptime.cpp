#include "uptime.hpp"

// Parse uptime file to extract the following data, in seconds:
//      up time: Wall clock since boot
//      idle time: combined idle time of all cpus
// Divide idle time by number of CPUs to obtain average idle time per CPU
// return struct containing up time and average idle time as strings
Sys_time get_up_idle_time(string uptime_filename_path, unsigned int number_of_CPUs){ // TODO: delete number_of_CPUs

    ifstream uptime_file(uptime_filename_path);

    if(!uptime_file.is_open()){
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    float up_time_secs = 0;
    float idle_time_secs = 0;

    getline(uptime_file, line);

    // split space-delimited line into two values
    string space_delimiter = " ";
    size_t pos = 0;
    pos = line.find(space_delimiter);
    up_time_secs = stof(line.substr(0, pos));
    line.erase(0, pos + space_delimiter.length());
    idle_time_secs = stof(line);

//    string up_time = seconds_to_time(up_time_secs);
//    string idle_time = seconds_to_time(idle_time_secs/number_of_CPUs); // average idle time per CPU

    return Sys_time{up_time_secs, idle_time_secs};
}

string seconds_to_time(unsigned int total_seconds){

    unsigned int hrs;
    unsigned int mins;
    unsigned int secs;

    hrs = total_seconds / 3600;
    mins = (total_seconds % 3600) / 60;
    secs = (total_seconds % 3600) % 60;

    return to_string(hrs) + " hours " + to_string(mins) + " minutes and " + to_string(secs) + " seconds";
}

Energy_used calculate_energy_used(float time_since_boot, float idle_time){

    float active_time = time_since_boot - idle_time; //TODO: ask if this is a valid way to calculate active time

    float cpu_active_power = 60; // Watts
    float cpu_idle_power = 10; // Watts

    float active_energy = cpu_active_power * active_time / 1000000;
    float idle_energy = cpu_idle_power * idle_time / 1000000;

    return Energy_used{active_energy, idle_energy};
}
