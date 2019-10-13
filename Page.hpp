//Rory Martin a1740203
//William Godfrey a1743033

#ifndef PAGE_H
#define PAGE_H

class Page {
    int age; //time page has existed
    int tlu; //time last used
    bool write;
public:
    //Contructor
    Page() {
        age = 0;
        tlu = 0;
        write = false;
    }

    //USEFUL FUNCTIONS
    //age
    void increaseAge() {
        age++;
    }
    void resetAge() {
        age = 0;
    }

    //time last used
    void setTLU(int newTime) {
        tlu = newTime;
    }
    int getTLU() {
        return tlu;
    }

    //write functions
    void toBeWritten()
    {
        write = true;
    }
    void written()
    {
        write = false;
    }

    //Destructor
    ~Page();
};

#endif
