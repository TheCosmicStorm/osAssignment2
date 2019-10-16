//Rory Martin a1740203
//William Godfrey a1743033

#ifndef PAGE_H
#define PAGE_H

#include <cmath>

class Page
{
    int age; //time page has existed
    int tlu; //time last used
    int page_number; //stores page number for printing
    bool write; //flag for whether the page need to be written to memory
    std::string refBit; //history of past 8 cycles
    int frequency; // frequency within the working set;


public:
    //Contructor
    Page(int pageNum)
    {
        age = 0;
        tlu = 0;
        refBit = "";

        write = false;
        page_number = pageNum;
    }

    //USEFUL FUNCTIONS
    // Age
    void increaseAge()
    {
        age++;
    }
    void resetAge()
    {
        age = 0;
    }
    int getAge()
    {
        return age;
    }

    // Time last used
    void setTLU(int newTime)
    {
        tlu = newTime;
    }
    int getTLU()
    {
        return tlu;
    }

    // Reference Bit
    void shiftRBit(std::string sel)
    {
        refBit = sel + refBit;
        refBit.pop_back();
    }
    void used()
    {
        refBit[0] = '1';
    }
    std::string getBit()
    {
        return refBit;
    }
    int integerARB()
    {
        int intEquiv = 0;
        for (int i = 0; i < refBit.length(); i++)
        {
            if (refBit[i] == '1')
            {
                intEquiv += pow(2,refBit.length()-i-1);
            }
        }
        return intEquiv;
    }
    void setBit(std::string newBit)
    {
        refBit = newBit;
    }

    //frequency functions
    void setFrequency(int freq)
    {
        frequency = freq;
    }
    int getFrequency()
    {
        return frequency;
    }

    // Write functions
    bool needsToBeWritten()
    {
        return write;
    }
    void toBeWritten()
    {
        write = true;
    }
    void written()
    {
        write = false;
    }

    //returns the page number (only in DEBUG)
    int getPageNum()
    {
        return page_number;
    }

    //Destructor
    ~Page()
    {

    }
};

#endif
