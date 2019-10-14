//Rory Martin a1740203
//William Godfrey a1743033

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "Page.hpp"
#include "MemoryMap.hpp"
#include "OS.hpp"

using namespace std;

vector<string> fileReader(string fileName) {
    vector<string> lines;
    string line;
    ifstream myfile ("input.txt", std::ifstream::in);
    // Checks that the file was opened properly
    if (myfile.is_open()) {
        // Stores each line of the input text file in the vector
        while (myfile.good()) {
            getline(myfile,line);
            lines.push_back(line);
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file." << '\n';
    }
    return lines;
}

//Sort the input into a vector of customers
vector<pair<char,string>> processInput(vector<string> input) {
    char command;
    string address;
    vector<pair<char,string>> traces;
    pair<char,string> temp;

    // Iterates through input vector sorting the traces into commands and addresses
    for (int i = 1; i < input.size()-1; i++) {
        stringstream ss;
        // Sorting input values
        ss << input.at(i);
        ss >> command;
        ss >> address;
        //std::cout << command << ' ';
        //td::cout << address << '\n';
        temp = make_pair(command,address);
        traces.push_back(temp);
    }
    //std::cout << traces.size() << '\n';
    return traces;
}

void checkArguments(int argc, char const *argv[], int pageSize, int numFrames, std::string algorithm) {
    // Checks for too few arguments
    if (argc < 5) {
        cout << "Too few arguments given." << '\n';
        exit(1);
    }

    // Checks if page size is reasonable
    if (pageSize < 1) {
        cout << "Page size is too small." << '\n';
        exit(1);
    }

    // Checks if the number of frames is reasonable
    if (numFrames < 1) {
        cout << "Number of frames is unreasonable." << '\n';
        exit(1);
    }

    // Checks if the algorithm exist
    if (algorithm != "FIFO" && algorithm != "LRU" && algorithm != "ARB" && algorithm != "WSARB") {
        cout << algorithm << '\n';
        cout << "Algorithm does not exist." << '\n';
        exit(1);
    }

    // Checks if there are too many arguments for FIFO or LRU
    if ((algorithm == "FIFO" || algorithm == "LRU") && argc > 5) {
        cout << "Too many arguments for the algorithm provided" << '\n';
        exit(1);
    }

    // Checks arguments for Algorithm ARB
    if (algorithm == "ARB") {
        if (argc != 7) {
            cout << "Incorrect number of arguments for ARB." << '\n';
            exit(1);
        }

        int a = stoi(argv[5]);
        if (a < 1 || a > 8) {
            cout << "Invalid a." << '\n';
            exit(1);
        }

        int b = stoi(argv[6]);
        if (b < 1 || b > 10) {
            cout << "Invalid b." << '\n';
            exit(1);
        }
    }

    // Checks arguments for algorithm WSARB
    if (algorithm == "WSARB") {
        if (argc != 8) {
            cout << "Too many arguments for WSARB." << '\n';
            exit(1);

            int a = stoi(argv[5]);
            if (a < 1 || a > 8) {
                cout << "Invalid a." << '\n';
                exit(1);
            }

            int b = stoi(argv[6]);
            if (b < 1 || b > 10) {
                cout << "Invalid b." << '\n';
                exit(1);
            }

            int delta = stoi(argv[7]);
            if (b < 1 || b > 20) {
                cout << "Invalid delta" << '\n';
                exit(1);
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    int pageSize = stoi(argv[2]);
    int numFrames = stoi(argv[3]);
    string algorithm = argv[4];
    checkArguments(argc, argv, pageSize, numFrames, algorithm);
    OS os (pageSize);
    if (argc == 7) {
        os.ARB(stoi(argv[5]), stoi(argv[6]));
    }
    else if (argc == 8) {
        os.WSARB(stoi(argv[5]), stoi(argv[6]), stoi(argv[7]));
    }
    vector<string> inputLines = fileReader(argv[1]);
    vector<pair<char,string>> traces = processInput(inputLines);
    os.initialiseOS(traces);
    os.runOS(algorithm, numFrames);
    os.printPages();
    return 0;
}
