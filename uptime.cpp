#include "uptime.hpp"


vector<string> get_uptime(string uptime_filename_path){

    ifstream uptime_file(uptime_filename_path);

    if(!uptime_file.is_open()){
        cerr << "Input file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }
    string line;

    getline(uptime_file, line);


    string space_delimiter = " ";
    vector<string> fields{};

    size_t pos = 0;
    pos = line.find(space_delimiter);
    fields.push_back(line.substr(0, pos));
    line.erase(0, pos + space_delimiter.length());
    fields.push_back(line);

    return fields;
}