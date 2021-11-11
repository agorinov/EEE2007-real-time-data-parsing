#include "Memory.hpp"

string get_memory_stat(string line, string field){

    // checks if line starts with field, followed by some number of spaces, then digits
    // if so, returns digits

    smatch m;
    regex reg_exp_MemFree("^" + field + "\\s+(\\d+)");
    if (regex_search(line, m, reg_exp_MemFree)){
        return m[1];
    }
}