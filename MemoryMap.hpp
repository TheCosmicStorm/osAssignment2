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
public:
    //Constructor
    MemoryMap(int allocatedSpace) {
        // Initializes empty vector onto memory map
        num_frames = allocatedSpace;
        std::vector<Page*> empty (num_frames);
        working_memory.push_back(empty);
    }

    // Determines whether a page is in working_memory
    bool findPage(Page* page) {
        for (int j = 0; j < num_frames; j++) {
            if (page == working_memory[working_memory.size()-1][j]) {
                return true;
            }
        }
        return false;
    }

    // Determines based on the algorithm, which page/frame gets replaced
    // Has 4 unique applications/ algorithms
    Page* determinePageToReplace(std::string algorithm) {
        int current_page = 0;// How is next page found/ updated
        // This value is used as an iterator
        // Needs the position of whatever page it is up to
        
        // Where is page value stored?
        
        
        // If frame space quota not yet full; populate
        if (working_memory[working_memory.size()].size() < num_frames) {
            for (int i = 0; i < num_frames; i++) {
                working_memory[working_memory.size()][i].push_back(disk_memory[current_page]);
            }
        }
        
        //First In, First Out implementation
        if (algorithm == "FIFO") {
            Page* largestCurrAge;
    
            // Find page to replace with largest age, in the current frame
            for (int i = 0; i < num_frames; i++) {
                if (working_memory[working_memory.size()][i].getAge() > largestCurrAge.getAge()) {
                    largestCurrAge.getAge() = working_memory[working_memory.size()][i].getAge();
                    // Return page position to replace?
                }
            }
            return largestCurrAge;
        }

        // Least Recently Used implementation
        else if (algorithm == "LRU") {
            Page* lowestTimeUsed;
            
            // Find page to replace with least recently used
            for (int i = 0; i < num_frames; i++) {
                if (working_memory[working_memory.size()][i].getTLU() > lowestTimeUsed.getTLU()) {
                    lowestTimeUsed.getTLU() = working_memory[working_memory.size()][i].getTLU();
                }
                // TLU must be reset to 0 for this case. Put in replace or here?
                   if (disk_memory[current_page] == working_memory[working_memory.size()][i].getTLU() &&
                       i = num_frames-1) {
                       working_memory[working_memory.size()][i].setTLU(0);
                   }
            }
            return lowestTimeUsed;
        }

        // Additional Reference Bit implementation
        else if (algorithm == "ARB") {
            Page* scrambledBits, lowestTimeUsed;
            // To begin, need to scramble each the history of each page TLU.
            // A is the number of bits to shift
            // B is length of time interval
            
            // Scramble every interval of inB
            if (current_page % inB == 0 && current_page != 0) {
                for (int i = 0; i < num_frames; i++) {
                    scrambledBits = working_memory[working_memory.size()][i].getTLU();
                    // Right shift by inA bits.
                    // Update new value.
                    working_memory[working_memory.size()][i].getTLU() = scrambledBits;
                }
            }
            
            // Otherwise find page to replace with least recently used
            for (int i = 0; i < num_frames; i++) {
                if (working_memory[working_memory.size()][i].getTLU()lowestTimeUsed.getTLU()) {
                    lowestTimeUsed.getTLU()working_memory[working_memory.size()][i].getTLU();
                }
            // TLU must be reset to 0 for this case. Put in replace or here?
                if (disk_memory[current_page] == working_memory[working_memory.size()][i].getTLU() &&
                i = num_frames-1) {
                    working_memory[working_memory.size()][i].setTLU(0);
                }
            }
            return lowestTimeUsed;
        }

        // Working-Set Additional Reference Bit implementation
        else if (algorithm == "WSARB") {
            // Combines shifting the bits with the last one in ARB but additionally uses frequency counter to determine what is replaced
            
        }
    }

    // Replaces page in working with new page
    bool replacePage(Page* prevPage, Page* newPage) {
        // Replace based on position or value?
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
    }
};

#endif
