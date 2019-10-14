//Rory Martin a1740203
//William Godfrey a1743033

#ifndef PAGE_H
#define PAGE_H

class Page {
    int age; //time page has existed
    int tlu; //time last used
    bool write; //flag for whether the page need to be written to memory
    int page_number; //stores page number for printing
public:
    //Contructor
    Page(int pageNum) {
        age = 0;
        tlu = 0;
        write = false;
        page_number = pageNum;
    }

    //USEFUL FUNCTIONS
    // Age
    void increaseAge() {
        age++;
    }
    void resetAge() {
        age = 0;
    }
    int getAge() {
        return age;
    }

    // Time last used
    void setTLU(int newTime) {
        tlu = newTime;
    }
    int getTLU() {
        return tlu;
    }

    // Write functions
    bool needsToBeWritten() {
        return write;
    }
    void toBeWritten() {
        write = true;
    }
    void written() {
        write = false;
    }

    //returns the page number (only in DEBUG)
    int getPageNum() {
        return page_number;
    }

    //Destructor
    ~Page() {

    }
};

#endif
