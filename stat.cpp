#include "stat.hpp"

// Parse the stat file using regex and for each cpu, extract the following data:
//      name: eg cpu5
//      user: normal processes executing in user mode
//      nice: niced processes executing in user mode
//      system: processes executing in kernel mode
//      idle: twiddling thumbs
// store data in a struct
// return vector of structs which scales according to number of CPUs
vector<CPU> get_cpu_stats(string filename){

    ifstream stat_file(filename);

    if(!stat_file.is_open()) {
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    vector<CPU> all_CPUs;
    string line;
    while (getline(stat_file, line)) {
        smatch m;
        regex cpu_reg_exp(R"(^(cpu\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))");
        if (regex_search(line, m, cpu_reg_exp)) {

            CPU cpu{};
            cpu.name = m[1];
            cpu.busy_time = stof(m[2]);
            cpu.nice_time = stof(m[3]);
            cpu.system_time = stof(m[4]);
            cpu.idle_time = stof(m[5]);

            all_CPUs.push_back(cpu);
        }

          //getting number of interrupts
//        regex intr_reg_exp(R"(^intr\s+(\d+))");
//        if (regex_search(line, m, intr_reg_exp)) {
//
//
//        }

        }
    stat_file.close();
    return all_CPUs;
}

// convert CPU stats to percentages and store them as float values in an array
// return a pointer to array
float *convert_to_percent(float busy_time, float nice_time, float system_time, float idle_time){

   static float cpu_perc[4]; // needs to be static otherwise output is weird //TODO: find out why

    float total = busy_time + nice_time + system_time + idle_time;

    cpu_perc[0] = busy_time / total * 100;
    cpu_perc[1] = nice_time / total * 100;
    cpu_perc[2] = system_time / total * 100;
    cpu_perc[3] = idle_time / total * 100;


    return cpu_perc;
}

string get_intr_serv(string filename){

    ifstream stat_file(filename);

    if(!stat_file.is_open()) {
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string interrupts_serviced = "N/A";
    while (getline(stat_file, line)) {
        smatch m;

    //getting number of interrupts
        regex intr_reg_exp(R"(^intr\s+(\d+))");
        if (regex_search(line, m, intr_reg_exp)) {

            interrupts_serviced =  m[1];
        }
    }

    stat_file.close();
    return interrupts_serviced;
}


