#include "meminfo.hpp"

// parse meminfo pseudofile to find memory value corresponding to specified field
// return memory value in kB
string getMemoryStats(string meminfoPseudofilePath, string field){

    string result = "N/A"; // if regex fails to find match, function returns "N/A"
    ifstream meminfoFile(meminfoPseudofilePath);

    if(!meminfoFile.is_open()){
        cerr << "meminfo could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }
    string line;

    while (getline(meminfoFile, line)) {

        smatch m;
        // check if line starts with field, followed by some number of spaces, then digits
        // if so, returns digits
        regex memRegExp("^" + field + "\\s+(\\d+)");
        if (regex_search(line, m, memRegExp)) {
            // cout << "line: " << m[0] << endl;
            result = m[1];
            break;
        }
    }
    meminfoFile.close();
    return result;
}

// Convert kb from string to int, perform kB to MB conversion, return value as string with "MB" appended
string kiloToMegabytes(string& kb){
    return to_string(stoi(kb)/1024) + " MB";
}