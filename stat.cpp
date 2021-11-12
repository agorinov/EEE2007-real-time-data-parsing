#include "stat.hpp"

void get_cpu_stats(string filename){


    ifstream stat_file(filename);

    if(!stat_file.is_open()) {
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int cpu_counter = 0;
    int busy_time, nice_time, system_time, idle_time;

    while (getline(stat_file, line)) {

        smatch m;
        regex reg_exp(R"(^cpu\d+\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))");
        if (regex_search(line, m, reg_exp)) {
            cpu_counter++;
            busy_time = stoi(m[1]);
            nice_time = stoi(m[2]);
            system_time = stoi(m[3]);
            idle_time = stoi(m[4]);
        }
    }

    cout << "busy: " << busy_time << endl;
    cout << "nice: " << nice_time << endl;
    cout << "system: " << system_time << endl;
    cout << "idle: " << idle_time << endl;
    cout << "cpu cores: " << cpu_counter << endl;

    stat_file.close();

}