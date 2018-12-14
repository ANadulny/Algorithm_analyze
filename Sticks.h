/*
@title Zadanie 9: Znajdowanie i zliczanie kombinacji takich 6 elementow (z tablicy S elementowej liczb naturalnych mniejszych badz rownych S) za pomocą ktorych mozna zbudowac kwadrat.
@author Adrian Nadulny
index: 283706
*/
#ifndef STICKS_H_INCLUDED
#define STICKS_H_INCLUDED
class Sticks {

        int stickNumber; //unsigned
        int *stickTable;

    public:
        Sticks(int number);

        int getStickNumber();
        int* getStickTable();
        int* getNewStickTable();
        void setStickNumber(int number);
        void generateStickTable();
        ~Sticks();
};

Sticks::Sticks(int number) {
    stickNumber = number;
    stickTable = new int[number];
}

int Sticks::getStickNumber() {
    return stickNumber;
}

int* Sticks::getStickTable() {
    return stickTable;
}

int* Sticks::getNewStickTable() {
    int *newStickTable = new int[stickNumber];
    for( int i = 0; i < stickNumber; i++ ) {
        newStickTable[i] = stickTable[i];
    }
    return newStickTable;
}

void Sticks::setStickNumber(int number) {
    this->stickNumber = number;
    delete []stickTable;
    stickTable = new int[number];
    generateStickTable();
}

void Sticks::generateStickTable () {
    srand(time(NULL));
    for( int i = 0; i < stickNumber; i++ ) {
        stickTable[i] = rand() % stickNumber + 1;
    }
}

Sticks::~Sticks() {
    delete []stickTable;
    stickTable = nullptr;
}

#endif // STICKS_H_INCLUDED
