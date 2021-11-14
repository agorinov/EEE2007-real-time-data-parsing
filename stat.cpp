#include "stat.hpp"

string get_cpu_stats(string line) {

    stringstream linestream(line);
    string busy, nice, system, idle;
    string cpu_stat_string = "";
    string first_token;

    getline(linestream, first_token, ' ');

    //checks if line starts with "cpuN" where N is a digit
    if (first_token.find('cpu') && any_of(first_token.begin(), first_token.end(), ::isdigit)) {
//        cout << line << endl;

        linestream >> busy >> nice >> system >> idle;
        cpu_stat_string = first_token + " " + busy + " " + nice + " " + system + " " + idle;
    }

    return cpu_stat_string;
}

string get_cpu_percetages(string cpu_stat){

}



//    ifstream stat_file(filename);
//
//    if(!stat_file.is_open()) {
//        cerr << "Input file could not be opened -- exiting." << endl;
//        exit(EXIT_FAILURE);
//    }
//
//    string line;
//    string cpu_name;
//    int cpu_counter = 0;
//    float busy_time, nice_time, system_time, idle_time, total;
//    float busy_percent, nice_percent, system_percent, idle_percent, total_percent;
//
//    cout << "---------------------------------------------------------------------------------------------" << endl;
//    cout << "Total CPU Cores: " << "CPU_PLACEHOLDER" << endl;
//    cout << "---------------------------------------------------------------------------------------------" << endl;
//    cout << "CPU" << setw(11) << "busy" << setw(10)  << "idle"  << setw(10) << "system" << setw(10) <<  "nice" << endl;
//
//    while (getline(stat_file, line)) {
//
//        smatch m;
//        regex reg_exp(R"(^(cpu\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))");
//        if (regex_search(line, m, reg_exp)) {
////            cpu_counter++;
//            cpu_name = m[1];
//            busy_time = stof(m[2]);
//            nice_time = stof(m[3]);
//            system_time = stof(m[4]);
//            idle_time = stof(m[5]);
//
//            total = busy_time + nice_time + system_time + idle_time;
//            busy_percent = busy_time/total*100;
//            nice_percent = nice_time/total*100;
//            system_percent = system_time/total*100;
//            idle_percent = idle_time/total*100;
//
//            cout << "cpu" << cpu_counter++;
////            cout.precision(2);
//            cout << setw(10) << busy_percent;
//            cout << setw(10) << idle_percent;
//            cout << setw(10) << system_percent;
//            cout << setw(10) << nice_percent << endl;
//
////            cout << boost::format("%f2.2 %f2.2 %f2.2 %f2.2") %  busy_percent % idle_percent % system_percent % nice_percent << endl;
//
//
//
//        }
//    }
//
////    cout << "busy: " << busy_time << endl;
////    cout << "nice: " << nice_time << endl;
////    cout << "system: " << system_time << endl;
////    cout << "idle: " << idle_time << endl;
////    cout << "cpu cores: " << cpu_counter << endl;
//
//    stat_file.close();
