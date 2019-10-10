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
    std::vector<std::vector<Page*> > memory_map;
    
public:
    //Constructor
    MemoryMap() {
        // Initializes empty vector onto memory map
        std::vector<Page*> empty;
        memory_map.push_back(empty);
    }
    
    // Converts n-bits hexadecimal numbers to base 10
    int hexConvert(std::string hexadecimal) {
        int converted = 0;
        
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
    
    // Prints the entire current map
    void printMap() {
        std::cout << "Current Map:" << endl;
        for (int i = 0; i < memory_map.size(); i++) {
            for (int j = 0; j < memory_map[i].size(); j++) {
                std::cout << memory_map[i][j] << " ";
            }
        std::cout << endl;
        }
    }
    
    // Prints the current maps last unit
    void printCurrent() {
        std::cout << "Current Time:" << endl;
        for (int i = 0; i < memory_map[memory_map.size()-1].size(); i++) {
            std::cout << memory_map[memory_map.size()-1][i] << " ";
        }
        std::cout << endl;
    }
    
    // Deconstructor
    ~MemoryMap() {
        // Cleans memory and deletes entire memory queue
        for (int i = 0; i < memory_map.size(); i++) {
            for (int j = 0; j < memory_map[i].size(); j++) {
                delete memory_map[i][j];
            }
        }
    }
};

#endif

