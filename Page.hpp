#ifndef PAGE_H
#define PAGE_H

class Page {
    int age; //time page has existed
    int tlu; //time last used
public:
    //Contructor
    Page() {
        age = 0;
        tlu = 0;
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

    //Destructor
    ~Page();
};

#endif