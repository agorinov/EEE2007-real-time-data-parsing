#include "meminfo.hpp"

string get_memory_stats(string meminfo_filename_path, string field){

    string result = "No data";
    // checks if line starts with field, followed by some number of spaces, then digits
    // if so, returns digits

    ifstream meminfo_file(meminfo_filename_path);

    if(!meminfo_file.is_open()){
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }
    string line;

    while (getline(meminfo_file, line)) {

        smatch m;
        regex reg_exp("^" + field + "\\s+(\\d+)");
        if (regex_search(line, m, reg_exp)) {
            //converting from string to int for kB to MB conversion, then back to string
            result = to_string(stoi(m[1])/1024) + " MB";
            break;
        }
    }
    meminfo_file.close();
    return result;
}