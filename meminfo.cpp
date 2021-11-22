#include "meminfo.hpp"

string getMemoryStats(string meminfoPseudofilePath, string field){

    string result = "No data";
    // checks if line starts with field, followed by some number of spaces, then digits
    // if so, returns digits

    ifstream meminfoFile(meminfoPseudofilePath);

    if(!meminfoFile.is_open()){
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }
    string line;

    while (getline(meminfoFile, line)) {

        smatch m;
        regex memRegExp("^" + field + "\\s+(\\d+)");
        if (regex_search(line, m, memRegExp)) {
            //converting from string to int for kB to MB conversion, then back to string
            result = to_string(stoi(m[1])/1024) + " MB";
            break;
        }
    }
    meminfoFile.close();
    return result;
}