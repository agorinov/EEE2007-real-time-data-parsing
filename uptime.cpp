#include "uptime.hpp"


vector<string> get_uptime(string uptime_filename_path){

    ifstream uptime_file(uptime_filename_path);

    if(!uptime_file.is_open()){
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    int sys_up_time = 0;
    int sys_idle_time = 0;
    vector<string> sys_up_idle{};

    getline(uptime_file, line);


    string space_delimiter = " ";

//    size_t pos = 0;
//    pos = line.find(space_delimiter);
//    fields.push_back(line.substr(0, pos));
//    line.erase(0, pos + space_delimiter.length());
//    fields.push_back(line);

    size_t pos = 0;
    pos = line.find(space_delimiter);
    sys_up_time = stoi(line.substr(0, pos));
    line.erase(0, pos + space_delimiter.length());
    sys_idle_time = stoi(line);

    int seconds, hours, minutes;
    seconds = sys_up_time;
    minutes = seconds / 60;
    hours = minutes / 60;
    sys_up_idle.push_back( "UP for " + to_string(hours) + " hours " + to_string(minutes%60) + " minutes and " +
                                   to_string(seconds%60) + " seconds");

    seconds = sys_idle_time;
    minutes = seconds / 60;
    hours = minutes / 60;
    sys_up_idle.push_back( "IDLE for " + to_string(hours) + " hours " + to_string(minutes%60) + " minutes and " +
                           to_string(seconds%60) + " seconds");



    return sys_up_idle;
}