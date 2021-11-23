#include "meminfo.hpp"

// Parse the meminfo file using regex, searching for line containing the string passed to the function
string getMemoryStats(string meminfoPseudofilePath, string field){

    string result = "N/A"; // if regex fails to find match, function returns "N/A"
    // checks if line starts with field, followed by some number of spaces, then digits
    // if so, returns digits

    ifstream meminfoFile(meminfoPseudofilePath);

    if(!meminfoFile.is_open()){
        cerr << "meminfo could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }
    string line;

    while (getline(meminfoFile, line)) {

        smatch m;
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