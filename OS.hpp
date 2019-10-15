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
    int writes;

    //ARB and WSARB
    int a;
    int b;
    int delta;
    std::string empty_ARB;

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
    OS (int pageSize) {
        page_size = pageSize;
        time = 0;
        reads = 0;
        writes = 0;
        a = 0;
        b = 0;
        delta = 0;
    }

    //function to add extra arguments for ARB
    void ARB(int inA, int inB) {
        a = inA;
        b = inB;
    }

    //function to add extra arguments for WSARB
    void WSARB(int inA, int inB, int inDelta) {
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
            commands.push_back(command);
            address = hexConvert(std::get<1>(traces[i]));
            addresses.push_back(address);

            // Checks if currrent page number greater than the largest
            pageNumber = address/page_size;
            if (pageNumber > largest) {
                largest = pageNumber;
            }
        }

        // Sets Bit to intialise length
        for (int i = 0; i < a; i++) {
            empty_ARB += "0";
        }

        // Fills the disk memory with largest page number + 1 pages
        Page* temp;
        for (int i = 0; i < largest+1; i++) {
            temp = new Page (i);
            disk_memory.push_back(temp);
            disk_memory[i]->setBit(empty_ARB);
        }
    }

    //Runs the page replacement simulator
    void runOS(std::string algorithm, int numFrames) {
        MemoryMap map (numFrames);
        int pageNumber;
        Page* incomingPage;
        Page* pageToReplace;
        //runs through all the traces simulating the page replacement algorithm
        for (int i = 0; i < commands.size(); i++) {

            time++;
            pageNumber = addresses[i]/page_size;
            incomingPage = disk_memory[pageNumber];

            //DEBUG
            // std::cout << "Time: " << time << ' ';
            // std::cout << "Page: "<< pageNumber << ' ';

            //checks if the page will need to be written to disk if it is removed
            if (commands[i] == 'W') {
                incomingPage->toBeWritten();
            }

            //Checks to see if the current time is in the middle of a
            // bit shift interval. If so it will shift the incomingPage
            if ((algorithm == "ARB" || algorithm == "WSARB") && ((time-1)%b != 0 || time-1 == 0)){
                incomingPage->used();
            }

            //If at the begining of an interval, run intervalShift
            if ((algorithm == "ARB" || algorithm == "WSARB") && (time-1) % b == 0) {
                map.intervalShift();
                incomingPage->used();
            }

            //checks if page is currently in frames/working memory
            if (!map.findPage(incomingPage)) {
                //DEBUG
                // std::cout << "MISS: " << ' ';

                //If page is not in working memory it must be read from the disk
                reads++;

                //determines the page to replace based on the algorithm
                pageToReplace = map.determinePageToReplace(algorithm);

                //replaces page, ensuring that any necessay parameters are reset
                map.replacePage(pageToReplace,incomingPage);
                if (pageToReplace != nullptr) {
                    pageToReplace->resetAge();

                    //checks if the page needs to be written to the disk
                    if (pageToReplace->needsToBeWritten()) {
                        writes++;
                        pageToReplace->written();
                    }

                    if (algorithm == "ARB" || algorithm == "WSARB") {
                        pageToReplace->setBit(empty_ARB);
                    }
                }
            }
            //DEBUG
            // else {
            //     std::cout << "HIT:  " << ' ';
            // }
            //sets the time last used and ages all pages in memory
            incomingPage->setTLU(time);
            map.ageAll();

            //DEBUG
            // std::cout << "frames:" << ' ';
            // if (algorithm == "ARB" || algorithm == "WSARB") {
            //     map.printCurrentWithARB(empty_ARB);
            // }
            // else {
            //     map.printCurrent();
            // }
            //std::cout << writes << '\n';
        }
    }

    // Prints out the final input of the Paging System
    void printPages() {
        // First Line
        std::cout << "events in trace:    ";
        std::cout << addresses.size() << std::endl;

        // Second Line
        std::cout << "total disk reads:   ";
        std::cout << reads << std::endl;

        // Third Line
        std::cout << "total disk writes:  ";
        std::cout << writes << std::endl;

        // Fourth Line
        std::cout << "page faults:        ";
        std::cout << reads << std::endl;
    }

    //Destructor
    ~OS() {
        // Deletes all elements of disk_memory to clean up computer memory
        for (int i = 0; i < disk_memory.size(); i++) {
            delete disk_memory[i];
        }
    }
};
