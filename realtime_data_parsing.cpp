#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(){
    string line;

    // absolute path of input dummy file containing meminfo data
    ifstream meminfo_file("C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - "
                    "Computer Systems and Microprocessors\\projects\\realtime_data_parsing\\meminfo.txt");

    if(!meminfo_file.is_open()){
        cerr << "Output file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "---------------------------------------------------------------------------------------------" << endl;

    while (getline(meminfo_file, line)){
        smatch m;

        regex reg_exp_MemFree("^MemFree:\\s+(\\d+)"); // looks for line which starts with "MemFree:" followed by 1+ whitespace characters and then 1+ digits
        if (regex_search(line, m, reg_exp_MemFree)){
//            cout << m[0] << endl; // contains entire string captured by regular expression
            cout << "Free: " << m[1] << endl; // 1st capturing group: contains digits
            continue;
        }
        regex reg_exp_MemTotal("^MemTotal:\\s+(\\d+)"); // looks for line which starts with "MemTotal:" followed by 1+ whitespace characters and then 1+ digits
        if (regex_search(line, m, reg_exp_MemTotal)){
            cout << "Total: " << m[1] << endl; // 1st capturing group: contains digits
            continue;
        }
        regex reg_exp_Buffers("^Buffers:\\s+(\\d+)"); // looks for line which starts with "Buffers:" followed by 1+ whitespace characters and then 1+ digits
        if (regex_search(line, m, reg_exp_Buffers)){
            cout << "Buffers: " << m[1] << endl; // 1st capturing group: contains digits
            continue;
        }
        regex reg_exp_Cached("^Cached:\\s+(\\d+)"); // looks for line which starts with "Cached:" followed by 1+ whitespace characters and then 1+ digits
        if (regex_search(line, m, reg_exp_Cached)){
            cout << "Cached:" << m[1] << endl; // 1st capturing group: contains digits
            continue;
        }
    }
    meminfo_file.close();

    return 0;
}