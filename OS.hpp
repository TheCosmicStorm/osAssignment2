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

    // Converts n-bits hexadecimal numbers to base 10
    int hexConvert(std::string hexadecimal) {
        int converted = 0;

        //runs through each character of a hexadecimal string and adds it to
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
    OS (int pageSize) {
        page_size = pageSize;
        time = 0;
    }

    // Counts up the total number of pages that would be in disk_memory and then
    // creates that number of pages and stores them in disk_memory
    void initialiseOS(std::vector<std::pair<char,std::string>> traces) {

        //runs through all the traces finding the largest page number
        //also separates traces into the 2 vectors: commands and addresses
        char command;
        int address;
        int pageNumber;
        int largest = -1;
        for (i = 0; i < traces.size(); i++) {
            //separates trace into command and address
            command = traces[i].get<0>;
            commands.push_back(command);
            address = hexConvert(traces[i].get<1>);
            addresses.push_back(addresss);

            //checks if currrent page number greater than the largest
            pageNumber = address/page_size;
            if (pageNumber > largest) {
                largest = pageNumber;
            }
        }

        //fills the disk memory with largest page number + 1 pages
        Page* temp;
        for (int i = 0; i < largest+1; i++) {
            temp = new Page;
            disk_memory.push_back(temp)
        }
    }

    void runOS(std::string algorithm)
    {

    }

    //Destructor
    ~OS()
    {
        // Deletes all elements of disk_memory to clean up computer memory
        for (int i = 0; i < disk_memory.size(); i++)
        {
            delete disk_memory[i];
        }
    }
};