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
        cerr << "Stat file could not be opened -- exiting." << endl;
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

// receive core time stats as references and convert to percentages
void convertToPercent(float& busyTime, float& niceTime, float& systemTime, float& idleTime){

    float totalTime = busyTime + niceTime + systemTime + idleTime;

    busyTime = busyTime / totalTime * 100;
    niceTime = niceTime / totalTime * 100;
    systemTime = systemTime / totalTime * 100;
    idleTime = idleTime / totalTime * 100;

}
// parse stat file using regex and return number of interrupts serviced
string getInterruptsServiced(string filename){

    ifstream statFile(filename);

    if(!statFile.is_open()) {
        cerr << "Stat file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string interruptsServiced = "N/A";
    while (getline(statFile, line)) {
        smatch m;

    //get number of interrupts serviced
        regex intrRegExp(R"(^intr\s+(\d+))");
        if (regex_search(line, m, intrRegExp)) {

            interruptsServiced =  m[1];
        }
    }

    statFile.close();
    return interruptsServiced;
}
// parse stat file for number of context switches
string getContextSwitchCount(string filename){

    ifstream statFile(filename);

    if(!statFile.is_open()) {
        cerr << "Stat file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string contextSwitchCount;
    while (getline(statFile, line)) {
        smatch m;

        //get number of context switches
        regex ctxtRegExp(R"(^ctxt\s+(\d+))");
        if (regex_search(line, m, ctxtRegExp)) {
            contextSwitchCount =  m[1];
        }
    }

    statFile.close();
    return contextSwitchCount;
}
// convert large number into smaller number and multiplier
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

string getSwapRatio(string filename){

    ifstream stat_file(filename);

    if(!stat_file.is_open()) {
        cerr << "Stat file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string swapRatio = "N/A"; // if no match found, return N/A
    while (getline(stat_file, line)) {
        smatch m;

        //checks if beginning of line starts with "swap" then some spaces and then some number of digits
        regex swap_reg_exp(R"(^swap\s+(\d+))");
        if (regex_search(line, m, swap_reg_exp)) {
            swapRatio =  m[1];
        }
    }

    stat_file.close();
    return swapRatio;
}

string getPageRatio(string filename){

    ifstream stat_file(filename);

    if(!stat_file.is_open()) {
        cerr << "Stat file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    string pageRatio = "N/A"; // if no match found, return N/A
    while (getline(stat_file, line)) {
        smatch m;

        //checks if beginning of line starts with "page" then some spaces and then some number of digits
        regex page_reg_exp(R"(^page\s+(\d+))");
        if (regex_search(line, m, page_reg_exp)) {
            pageRatio =  m[1];
        }
    }

    stat_file.close();
    return pageRatio;

}
