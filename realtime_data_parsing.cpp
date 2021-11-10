#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main()
{
    string line;

    // absolute path of input dummy file containing meminfo data
    ifstream myfile("C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - Computer Systems and Microprocessors\\projects\\realtime_data_parsing\\meminfo.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            smatch m;

            regex regexp("^MemFree:\\s+(\\d+)"); // looks for line which starts with "MemFree:" followed by 1+ whitespace characters and then 1+ digits
            if (regex_search(line, m, regexp))
            {
                cout << m[0] << endl; // contains entire string captured by regular expression
                cout << m[1] << endl; // 1st capturing group: contains digits

                break;
            }
        }
        myfile.close();
    }
    else cout << "something went wrong" << endl;

    return 0;
}