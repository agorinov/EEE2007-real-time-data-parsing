#include "stat.hpp"

// Parse the stat file using regex and for each cpu, extract the following data:
//      name: eg cpu5
//      user: normal processes executing in user mode
//      nice: niced processes executing in user mode
//      system: processes executing in kernel mode
//      idle: twiddling thumbs
// store data in a struct
// return vector of structs which scales according to number of CPUs
vector<Core> getCpuStats(string filename){ //TODO: consider returning pointers to save memory

    ifstream statFile(filename);

    if(!statFile.is_open()) {
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    vector<Core> CPU;
    string line;
    while (getline(statFile, line)) {
        smatch m;
        regex cpuRegExp(R"(^(cpu\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+))");
        if (regex_search(line, m, cpuRegExp)) {

            Core cpu{};
            cpu.name = m[1];
            cpu.busyTime = stof(m[2]);
            cpu.niceTime = stof(m[3]);
            cpu.systemTime = stof(m[4]);
            cpu.idleTime = stof(m[5]);

            CPU.push_back(cpu);
        }
        }
    statFile.close();
    return CPU;
}

// convert Core stats to percentages and store them as float values in an array
// return a pointer to array
float *convertToPercent(float busyTime, float niceTime, float systemTime, float idleTime){

    static float cpuPercent[4]; // needs to be static otherwise output is weird

    float total = busyTime + niceTime + systemTime + idleTime;

    cpuPercent[0] = busyTime / total * 100;
    cpuPercent[1] = niceTime / total * 100;
    cpuPercent[2] = systemTime / total * 100;
    cpuPercent[3] = idleTime / total * 100;


    return cpuPercent;
}

string getInterruptsServiced(string filename){

    ifstream statFile(filename);

    if(!statFile.is_open()) {
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string interruptsServiced = "N/A";
    while (getline(statFile, line)) {
        smatch m;

    //getting number of interruptsServiced
        regex intrRegExp(R"(^intr\s+(\d+))");
        if (regex_search(line, m, intrRegExp)) {

            interruptsServiced =  m[1];
        }
    }

    statFile.close();
    return interruptsServiced;
}

string getContextSwitchCount(string filename){

    ifstream statFile(filename);

    if(!statFile.is_open()) {
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string contextSwitchCount;
    while (getline(statFile, line)) {
        smatch m;

        //getting number of interrupts
        regex ctxtRegExp(R"(^ctxt\s+(\d+))");
        if (regex_search(line, m, ctxtRegExp)) {
            contextSwitchCount =  m[1];
        }
    }

    statFile.close();
    return contextSwitchCount;
}

Quantity formatCount(string count){
    Quantity q {};
    q.number = stof(count);

//    cout << "count: " << q.number << endl;

    switch (count.length()){
        case 4:
        case 5:
        case 6: q.multiplier = "thousand"; q.number = stof(count)/1000; break;
        case 7:
        case 8:
        case 9: q.multiplier = "million"; q.number = stof(count)/1000000; break;
        case 10:
        case 11:
        case 12: q.multiplier = "billion"; q.number = stof(count)/1000000000; break;
        default: q.multiplier = ""; break;
    }

//    cout << "count: " << q.number << endl;
//    cout << "multiplier" << endl;

    return q;
}

//string get_swap_ratio(string filename){
//
//    ifstream stat_file(filename);
//
//    if(!stat_file.is_open()) {
//        cerr << "Input file could not be opened -- exiting." << endl;
//        exit(EXIT_FAILURE);
//    }
//
//    string line;
//    string  = "N/A";
//    while (getline(stat_file, line)) {
//        smatch m;
//
//        //getting number of interrupts
//        regex ctxt_reg_exp(R"(^ctxt\s+(\d+))");
//        if (regex_search(line, m, ctxt_reg_exp)) {
//            ctxt_switch_count =  m[1];
//        }
//    }
//
//    stat_file.close();
//    return ctxt_switch_count;
//}


