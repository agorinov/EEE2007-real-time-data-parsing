#include "stat.hpp"

void get_cpu_stats(string filename){


    ifstream stat_file(filename);

    if(!stat_file.is_open()) {
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string cpu_name;
    int cpu_counter = 0;
    float busy_time, nice_time, system_time, idle_time, total;
    float busy_percent, nice_percent, system_percent, idle_percent, total_percent;

    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "Total CPU Cores: " << "CPU_PLACEHOLDER" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << "CPU" << setw(11) << "busy" << setw(10)  << "idle"  << setw(10) << "system" << setw(10) <<  "nice" << endl;

    while (getline(stat_file, line)) {

        smatch m;
        regex reg_exp(R"(^(cpu\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))");
        if (regex_search(line, m, reg_exp)) {
//            cpu_counter++;
            cpu_name = m[1];
            busy_time = stof(m[2]);
            nice_time = stof(m[3]);
            system_time = stof(m[4]);
            idle_time = stof(m[5]);

            total = busy_time + nice_time + system_time + idle_time;
            busy_percent = busy_time/total*100;
            nice_percent = nice_time/total*100;
            system_percent = system_time/total*100;
            idle_percent = idle_time/total*100;

            cout << "cpu" << cpu_counter++;
//            cout.precision(2);
            cout << setw(10) << busy_percent;
            cout << setw(10) << idle_percent;
            cout << setw(10) << system_percent;
            cout << setw(10) << nice_percent << endl;

//            cout << boost::format("%f2.2 %f2.2 %f2.2 %f2.2") %  busy_percent % idle_percent % system_percent % nice_percent << endl;



        }
    }

//    cout << "busy: " << busy_time << endl;
//    cout << "nice: " << nice_time << endl;
//    cout << "system: " << system_time << endl;
//    cout << "idle: " << idle_time << endl;
//    cout << "cpu cores: " << cpu_counter << endl;

    stat_file.close();

}