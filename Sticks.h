#ifndef STICKS_H_INCLUDED
#define STICKS_H_INCLUDED
class Sticks {

        int stickNumber; //unsigned
        int *stickTable;

    public:
        Sticks(int number);

        int getStickNumber();
        int* getStickTable();
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

void Sticks::setStickNumber(int number)
{
    this->stickNumber = number;
    delete []stickTable;
    stickTable = new int[number];
    generateStickTable();
}

void Sticks::generateStickTable ()
{
    srand(time(NULL));
    for ( int i = 0; i < stickNumber; i++ ) {
        stickTable[i] = rand() % stickNumber + 1;
    }
}


Sticks::~Sticks(){
    delete []stickTable;
}


#endif // STICKS_H_INCLUDED
