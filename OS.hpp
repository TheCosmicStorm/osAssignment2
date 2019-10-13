//Rory Martin a1740203
//William Godfrey a1743033

#include "MemoryMap.hpp"
#include "Page.hpp"
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

class OS {
private:
    //stores list of read/write commands in trace order
    std::vector<char> commands;
    //stores list of memory address in trace order
    std::vector<int> addresses;
    //stores a list of all pages
    std::vector<Page*> disk_memory;
    //page size from input
    int page_size;
    //current operation
    int time;
    //number of reads
    int reads;
    //number of writes
    int writes

    //ARB and WSARB
    int a;
    int b;
    int delta;

    // Converts n-bits hexadecimal numbers to base 10
    int hexConvert(std::string hexadecimal) {
        int converted = 0;

        // Runs through each character of a hexadecimal string and adds it to
        // a base 10 int total
        for (int i = 0; i < hexadecimal.size(); i++) {
            // If a number: (num x 16^(7-i))
            if (isdigit(hexadecimal[i])) {
                converted += (hexadecimal[i]-'0') * (std::pow(16, 7-i));
            }
            // If a letter: (letterHex x 16^(7-i))
            else if (isalpha(hexadecimal[i])) {
                converted += ((hexadecimal[i]-'0')-39) * (std::pow(16, 7-i));
            }
        }
        return converted;
    }
    
public:
    //Constructor
    //inA, inB, inDelta all = 0 if not ARB or WSARB
    OS (int pageSize, int inA, int inB, int inDelta) {
        page_size = pageSize;
        time = 0;
        reads = 0;
        writes = 0;
        a = inA;
        b = inB;
        delta = inDelta;
    }

    // Counts up the total number of pages that would be in disk_memory and then
    // Creates that number of pages and stores them in disk_memory
    void initialiseOS(std::vector<std::pair<char,std::string>> traces) {

        // Runs through all the traces finding the largest page number
        // Also separates traces into the 2 vectors: commands and addresses
        char command;
        int address;
        int pageNumber;
        int largest = -1;
        for (int i = 0; i < traces.size(); i++) {
            // Separates trace into command and address
            command = std::get<0>(traces[i]);
            std::cout << command << ' ';
            commands.push_back(command);
            address = hexConvert(std::get<1>(traces[i]));
            std::cout << address << '\n';
            addresses.push_back(address);

            // Checks if currrent page number greater than the largest
            pageNumber = address/page_size;
            if (pageNumber > largest) {
                largest = pageNumber;
            }
        }

        // Fills the disk memory with largest page number + 1 pages
        Page* temp;
        for (int i = 0; i < largest+1; i++) {
            temp = new Page;
            disk_memory.push_back(temp);
        }
        std::cout << disk_memory.size() << '\n';
    }

    void runOS(std::string algorithm) {
        MemoryMap map;
        Page* incomingPage;
        for (int i = 0; i < commands.size(); i++) {
            incomingPage = addresses[i]/pageSize;
            
            map.determinePageToReplace(algorithm);
        }
    }

    //Destructor
    ~OS() {
        // Deletes all elements of disk_memory to clean up computer memory
        for (int i = 0; i < disk_memory.size(); i++) {
            delete disk_memory[i];
        }
    }
};
