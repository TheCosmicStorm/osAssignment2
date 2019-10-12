//Rory Martin a1740203
//William Godfrey a1743033

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "Customer.hpp"
#include "Queue.hpp"
#include "OperatingSystem.hpp"

using namespace std;

vector<string> fileReader(string fileName) {
    vector<string> lines;
    string line;
    ifstream myfile ("input.txt", std::ifstream::in);
    //checks that the file was opened properly
    if (myfile.is_open()) {
        //store each line of the input text file in the vector
        while (myfile.good()) {
            getline(myfile,line);
            lines.push_back(line);
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file" << '\n';
    }

    return lines;
}

//Sort the input into a vector of customers
vector<pair<char,string>> processInput(vector<string> input) {

    char command;
    string address;
    vector<pair<char,string>> traces;
    pair<char,string> temp;

    //iterates through input vector sorting the traces into commands and addresses
    for (int i = 1; i < input.size()-1; i++) {
        stringstream ss;
        //sorting input values
        ss << input.at(i);
        ss >> command;
        ss >> address;
        temp = make_pair(command,address)
        traces.push_back(temp);
    }

    return traces;
}

int main(int argc, char const *argv[]) {


    return 0;
}
