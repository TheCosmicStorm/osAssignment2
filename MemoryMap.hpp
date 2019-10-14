//Rory Martin a1740203
//William Godfrey a1743033

#ifndef MEMORYMAP_H
#define MEMORYMAP_H
#include "Page.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstddef>
#include <bitset>

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
        std::vector<Page*> empty (num_frames, nullptr);
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
    
    // Algorithm for FIFO
    Page* algorithmFIFO() {
        Page* largestCurrAge = working_memory[working_memory.size()-1][0];

        // Find page to replace with largest age, in the current frame
        for (int j = 1; j < num_frames; j++) {
            if (working_memory[working_memory.size()-1][j]->getAge() > largestCurrAge->getAge()) {
                largestCurrAge = working_memory[working_memory.size()-1][j];
            }
        }
        return largestCurrAge;
    }
    
    // Algorithm for LRU
    Page* algorithmLRU() {
        Page* leastRecentlyUsed = working_memory[working_memory.size()-1][0];
        // TLU = time last used
        // Find page to replace with least recently used
        for (int j = 1; j < num_frames; j++) {
            if (working_memory[working_memory.size()-1][j]->getTLU() < leastRecentlyUsed->getTLU()) {
                leastRecentlyUsed = working_memory[working_memory.size()-1][j];
            }
            else if (working_memory[working_memory.size()-1][j]->getTLU() == leastRecentlyUsed->getTLU()){
                if (working_memory[working_memory.size()-1][j]->getAge() > leastRecentlyUsed->getAge()) {
                    leastRecentlyUsed = working_memory[working_memory.size()-1][j];
                }
            }
        }
        return leastRecentlyUsed;
    }
    
    void scrambledBits(int interval) {
        // If current frame is on the interval and not at the start
        if (working_memory.size()-1 % interval == 0 && working_memory.size()-1 != 0) {
            // Shift all reference bits by inA
            for (int j = 0; j < num_frames; j++) {
                
            }
        }
        // FOR WILL:
        
        // Finally I need a function that allows me to update this refBit every time that page is used
        // Idk what it means by used but it gives the examples:
        // If the shift register contains 00000000, for example, then the page has not been used for eight time periods. A page that is used at least once in each period has a shift register value of 11111111. A page with a history register value of 11000100 has been used more recently than one with a value of 01110111.
        
        
        // Keep a-bit string for each page in memory each time it is used
        // Eg. 0000 has not been used yet.
        //     0110 has been used twice so far.
        //     1000 was most recently used
        // At interval, OS shifts all reference bits for each page by 1 right
        // Conversion part:
        // Therefore, the conversion of this 8bit number is its TLU
        // Update TLU after interval and run LRU
        
    }
    
    // Determines based on the 4 algorithms, which page/frame gets replaced
    Page* determinePageToReplace(std::string algorithm, int b) {
        // Whatevers in that current frame add 1, everything else add 0
        
        
        // For empty working_memory
        for (int j = 0; j < num_frames; j++) {
            working_memory[working_memory.size()-1][j] -> ageBit(1);
            if (working_memory[working_memory.size()-1][j] == nullptr) {
                return nullptr;
            }
        }
        //First In, First Out implementation
        if (algorithm == "FIFO") {
            return algorithmFIFO();
        }
        // Least Recently Used implementation
        else if (algorithm == "LRU") {
            return algorithmLRU();
        }
        // Additional Reference Bit implementation
        else if (algorithm == "ARB") {
            scrambledBits(b);
            return algorithmLRU();
         }
         //Working-Set Additional Reference Bit implementation
         else if (algorithm == "WSARB") {
             // Combines shifting the bits with the last one in ARB
             // Additionally uses frequency counter to determine what is replaced
             return algorithmLRU();
         }
        // Just to remove non-void return type warning
        return nullptr;
    }
    
    // Replaces page in working with new page
    void replacePage(Page* prevPage, Page* newPage) {
        std::vector<Page*> newTime (working_memory[working_memory.size()-1].begin(), working_memory[working_memory.size()-1].end());
        for (int i = 0; i < num_frames; i++) {
            if (newTime[i] == prevPage) {
                newTime[i] = newPage;
                break;
            }
        }
        working_memory.push_back(newTime);
    }

    // Prints the entire current map
    void printMap() {
        std::cout << "Current Map:" << std::endl;
        for (int i = 0; i < working_memory.size(); i++) {
            for (int j = 0; j < num_frames; j++) {
                if (working_memory[i][j] == nullptr) {
                    std::cout << "-1" << ' ';
                }
                else {
                    std::cout << working_memory[i][j]->getPageNum() << " ";
                }
            }
        std::cout << std::endl;
        }
    }

    // Prints the current maps last unit
    void printCurrent() {
        for (int i = 0; i < num_frames; i++) {
            if (working_memory[working_memory.size()-1][i] == nullptr) {
                std::cout << "-1" << ' ';
            }
            else {
                std::cout << working_memory[working_memory.size()-1][i]->getPageNum() << " ";
            }
        }
        std::cout << std::endl;
    }
    
    // Increases age of all in working memory
    void ageAll() {
        for (int i = 0; i < num_frames; i++) {
            if (working_memory[working_memory.size()-1][i] != nullptr) {
                working_memory[working_memory.size()-1][i]->increaseAge();
            }
        }
    }
    
    // Deconstructor
    ~MemoryMap() {
    }
};

#endif



/*
 Old method
 
 void scrambledBits(int shift, int interval) {
     // If current frame is on the interval and not at the start
     if (working_memory.size()-1 % interval == 0 && working_memory.size()-1 != 0) {
         // Shift all reference bits by inA
         for (int j = 0; j < num_frames; j++) {
             int scrambledBits = working_memory[working_memory.size()-1][j]->getTLU();
             // Converts integer to 8bit binary
             std::bitset<8> bin_x(scrambledBits);
             // Shifts bits by 'shift' amount
             int upd = scrambledBits << shift;
             // Updates values
             working_memory[working_memory.size()-1][j]->setTLU(upd);
         }
     }
 }
 */
