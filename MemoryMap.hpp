//Rory Martin a1740203
//William Godfrey a1743033

#ifndef MEMORYMAP_H
#define MEMORYMAP_H
#include "Page.hpp"
#include <string>
#include <vector>
#include <iostream>

class MemoryMap {
private:
    //stores references to Pages currently being operated on
    std::vector<std::vector<Page*> > working_memory;
    //stores the allocated space passed into the program
    int num_frames;
    int current_frame = 1;
    int current_page = 0;
public:
    //Constructor
    MemoryMap(int allocatedSpace) {
        // Initializes empty vector onto memory map
        num_frames = allocatedSpace;
        std::vector<Page*> empty (num_frames);
        working_memory.push_back(empty);
    }

    //determines based on the algorithm, which page/frame gets replaced
    //has 4 unique applications
    Page* determinePageToReplace(std::string algorithm) {
        //First In, First Out implementation
        if (algorithm == "FIFO") {
            Page* largestCurrAge;
            
            // If frame space quota not yet full; populate
            if (working_memory[0].size() < num_frames) {
                for (int i = 0; i < num_frames; i++) {
                    working_memory[current_frame][i].push_back(disk_memory[current_page]);
                }
            }
            
            // Otherwise find page to replace with largest age, in the current frame
            else {
                for (int i = 0; i < num_frames; i++) {
                    if (working_memory[current_frame][i].getAge() > largestCurrAge) {
                        largestCurrAge.getAge() = working_memory[current_frame][i].getAge();
                        // Return page position to replace?
                    }
                }
            }
            return largestCurrAge;
        }

        //Least Recently Used implementation
        else if (algorithm == "LRU")
        {
            /* code */
        }

        //Additional Reference Bit implementation
        else if (algorithm == "ARB")
        {

        }

        //Working-Set Additional Reference Bit implementation
        else if (algorithm == "WSARB")
        {
            /* code */
        }
        current_frame++;
        current_page++;
    }

    //replaces page in working with new page
    bool replacePage(Page* prevPage, Page* newPage) {

    }
    // Prints the entire current map
    void printMap() {
        std::cout << "Current Map:" << std::endl;
        for (int i = 0; i < working_memory.size(); i++) {
            for (int j = 0; j < num_frames; j++) {
                std::cout << working_memory[i][j] << " ";
            }
        std::cout << std::endl;
        }
    }

    // Prints the current maps last unit
    void printCurrent() {
        std::cout << "Current Time:" << std::endl;
        for (int i = 0; i < num_frames; i++) {
            std::cout << working_memory[working_memory.size()-1][i] << " ";
        }
        std::cout << std::endl;
    }

    // Deconstructor
    ~MemoryMap() {
        // Cleans memory and deletes entire memory queue
    }
};

#endif
