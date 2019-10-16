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
    // Stores working set given delta
    std::vector<std::vector<Page*> > working_set;
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

    Page* algorithmARB() {
        Page* leastRecentlyUsed = working_memory[working_memory.size()-1][0];
        int testRefBit;
        std::vector<Page*> sameARB;
        // Find page to replace with smallest ARB
        for (int j = 1; j < num_frames; j++) {
            testRefBit = working_memory[working_memory.size()-1][j]->integerARB();
            if (testRefBit < leastRecentlyUsed->integerARB()) {
                leastRecentlyUsed = working_memory[working_memory.size()-1][j];
                if (!sameARB.empty()) {
                    sameARB.clear();
                }
            }
            else if (testRefBit == leastRecentlyUsed->integerARB()){
                sameARB.push_back(leastRecentlyUsed);
                leastRecentlyUsed = working_memory[working_memory.size()-1][j];
            }
        }

        //FIFO if there are multiple of the smallest
        for (int i = 0; i < sameARB.size(); i++) {
            // std::cout << "Comparison" << '\n';
            // std::cout << leastRecentlyUsed->getPageNum() << ": " << leastRecentlyUsed->getAge() << '\n';
            // std::cout << sameARB[i]->getPageNum() << ": " << sameARB[i]->getAge() << '\n';;
            if (sameARB[i]->getAge() > leastRecentlyUsed->getAge()) {
                leastRecentlyUsed = sameARB[i];
            }
        }
        return leastRecentlyUsed;
    }

    //At predetermined intervals it will perform a right bitShift for all page
    // ARBs in memoryincomingPage
    void intervalShift() {
        //For ARB/WSARB and at interval, for used page => bitShift 1, else bit shift 0
        for (int j = 0; j < num_frames; j++) {
            if (working_memory[working_memory.size()-1][j] == nullptr) {
                continue;
            }
            else {
                working_memory[working_memory.size()-1][j]->shiftRBit("0");
            }
        }
    }

    // Determines based on the 4 algorithms, which page/frame gets replaced
    Page* determinePageToReplace(std::string algorithm) {

        // For empty working_memory
        for (int j = 0; j < num_frames; j++) {
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
            return algorithmARB();
         }
         //Working-Set Additional Reference Bit implementation
         else if (algorithm == "WSARB") {
             // Combines shifting the bits with the last one in ARB
             // Additionally uses frequency counter to determine what is replaced
             
             // Working Set
             // Identify the most recent set of pages given delta, if not longer used drops from set
             // Only stores no. once, ascending: this is locality the set of all numbers encompassed
             // If workset > size of pages left; process suspended?
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

    void printCurrentWithARB(std::string emptyARB) {
        for (int i = 0; i < num_frames; i++) {
            if (working_memory[working_memory.size()-1][i] == nullptr) {
                std::cout << "-1(" << emptyARB << ") ";
            }
            else {
                std::cout << working_memory[working_memory.size()-1][i]->getPageNum();
                std::cout << '(' << working_memory[working_memory.size()-1][i]->getBit() <<") ";
            }
        }
        std::cout << std::endl;
    }
    
    // Updates the working set
    std::vector<int> updWS(std::vector<int> pages_left) {
        std::vector<int> wS;

        for (unsigned int i = 0; i < pages_left.size(); i++) {
            // For first elementement
            if (i == 0) {
                wS.push_back(pages_left[i]);
            }
            // If element from pages_left missing from wS; add
            if (find(wS.begin(), wS.end(), pages_left[i]) == wS.end()) {
                wS.push_back(pages_left[i]);
            }
        }
        // Sort Ascending
        sort(wS.begin(), wS.end());
        return wS;
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
