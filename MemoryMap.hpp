//Rory Martin a1740203
//William Godfrey a1743033

#ifndef MEMORYMAP_H
#define MEMORYMAP_H
#include "Page.hpp"
#include <algorithm>
#include <string>
#include <vector>

class MemoryMap {
private:
    //stores references to Pages currently being operated on
    std::vector<std::vector<Page*> > working_memory;
    //stores the allocated space passed into the program
    int num_frames;
public:
    //Constructor
    MemoryMap(int allocatedSpace) {
        // Initializes empty vector onto memory map
        num_frames = allocatedSpace;
        std::vector<Page*> empty (num_frames);
        working_memory.push_back(empty);
    }

    // Prints the entire current map
    void printMap() {
        std::cout << "Current Map:" << endl;
        for (int i = 0; i < working_memory.size(); i++) {
            for (int j = 0; j < num_frames; j++) {
                std::cout << working_memory[i][j] << " ";
            }
        std::cout << endl;
        }
    }

    // Prints the current maps last unit
    void printCurrent() {
        std::cout << "Current Time:" << endl;
        for (int i = 0; i < num_frames; i++) {
            std::cout << working_memory[working_memory.size()-1][i] << " ";
        }
        std::cout << endl;
    }

    // Deconstructor
    ~MemoryMap() {
        // Cleans memory and deletes entire memory queue
        for (int i = 0; i < working_memory.size(); i++) {
            for (int j = 0; j < num_frames; j++) {
                delete working_memory[i][j];
            }
        }
    }
};

#endif
