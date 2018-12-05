#include <iostream>
#include <chrono>
#include <random>
#include <chrono>
#include <fstream>
#include "Sticks.h"
#include "Algorithm.h"

using namespace std;

void UI();
int newStickNumber();
void optionScreen (Sticks &sticks);
void changeStick(Sticks &sticks);
void generateStickTableElements(Sticks &sticks);
void showStickTableElements(Sticks &sticks);
void generateOwnStickTableElements(Sticks &sticks);
void algorithmsTimeMeasure(Sticks &sticks);

//int AlgorithmNaive(int table[], int lengt);

int main()
{
    UI();
    return 0;
}

void UI()
{
    cout << "Please enter the number of sticks:" << endl;

    int stickNumber = newStickNumber();

    // testing
    //cout << "Sticks number: " << stickNumber << endl;

    //Poczatek wypelniania tablicy S elementowej
    Sticks sticks(stickNumber);
    sticks.generateStickTable();

    int decision;

    while(1)
    {
        system("clear");
        optionScreen( sticks );
        cin >> decision;

        if(cin.fail() )
        {
            cin.clear();
            cin.ignore(150, '\n');
            continue;
        }

        if(decision < 1 || decision > 6)
            continue;

        switch(decision)
        {
            case 1:
                changeStick( sticks );
                break;
            case 2:
                generateStickTableElements(sticks);
                break;
            case 3:
                generateOwnStickTableElements(sticks);
                break;
            case 4:
                algorithmsTimeMeasure(sticks);
                break;
            case 5:
                showStickTableElements(sticks);
                break;
            default:
                return;
        }
    }
}

int newStickNumber()
{
    int stickNumber;
    do {

        cin >> stickNumber;
        if(cin.fail() )
        {
            cin.clear();
            cin.ignore(150, '\n');
        }
    } while ( stickNumber < 6 );
    return stickNumber;
}

void optionScreen (Sticks &sticks)
{
    cout<<"Current S value: "<<sticks.getStickNumber()<<endl;
	cout<<"Write correct number:"<<endl;
	cout<<"[1] Change sticks number S:"<<endl;
	cout<<"[2] Generate random value for sticks table." <<endl;
	cout<<"[3] Generate own stick table." <<endl;
	cout<<"[4] Measure time of algorithms." <<endl;
	cout<<"[5] Show elements from stick table." <<endl;
	cout<<"[6] End program" <<endl;
}

void changeStick(Sticks &sticks)
{
    system("clear");
    cout<<"Write new sticks number S:"<<endl;
    int newSticksNumber = newStickNumber();
    sticks.setStickNumber(newSticksNumber);
}

void generateStickTableElements(Sticks &sticks)
{
    sticks.generateStickTable();
}

void showStickTableElements(Sticks &sticks)
{
    system("clear");
    for( int i = 0; i < sticks.getStickNumber(); i++)
    {
        cout << i << ":" << *(sticks.getStickTable()+i) <<"; ";
    }

    string goBack;
    cout << "\nPress key to go back to main panel."<<endl;
    cin >> goBack;
}

void generateOwnStickTableElements(Sticks &sticks)
{
    int newElem;
    for (int i = 0; i < sticks.getStickNumber(); i++)
    {
        system("clear");
        cout << "Write: " << sticks.getStickNumber() - i << " new elements." << endl;
        cout << "Element can not be more than " << sticks.getStickNumber() << endl;
        do {
            cin >> newElem;
            if(cin.fail() )
            {
                cin.clear();
                cin.ignore(150, '\n');
            }
        } while ( newElem < 1 || newElem > sticks.getStickNumber() );
        *(sticks.getStickTable()+i) = newElem;
    }
}

void algorithmsTimeMeasure(Sticks &sticks)
{
    system("clear");
    int stickTable[sticks.getStickNumber()];

    int squaresNumber;
    //Algorithm algorithm(sticks); //zamiast stickTable to stick.getStickTable()
    Algorithm algorithm;
    cout<<"[1] NaiveAlgorithm"<<endl;

    ofstream naiveAlgorithmFile;
    naiveAlgorithmFile.open("naiveAlgorithm.txt");
    naiveAlgorithmFile << "Naive Algorithm:\n";
    naiveAlgorithmFile << "===========================================\n";

    cout << "===========================================" << endl;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    squaresNumber = algorithm.AlgorithmNaive(sticks.getStickTable(), sticks.getStickNumber(), naiveAlgorithmFile );
    cout << squaresNumber << ": Squares number" << endl;
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "===========================================" << endl;
    cout << "Algorithm time: " << elapsed_seconds.count() << endl;

    naiveAlgorithmFile << "Squares number: " << squaresNumber << "\n";
    naiveAlgorithmFile << "===========================================\n";
    naiveAlgorithmFile << "Algorithm time: " << elapsed_seconds.count() << "\n";
    naiveAlgorithmFile.close();

    cout << endl;

	cout<<"[2] AlgorithmMyHeuristic" <<endl;

    ofstream myHeuristicAlgorithmFile;
	cout << "===========================================" << endl;
    start = std::chrono::system_clock::now();
    cout << algorithm.AlgorithmMyHeuristic(sticks.getStickTable(), sticks.getStickNumber() ) << ": Squares number" << endl;
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "===========================================" << endl;
    cout << "Algorithm time: " << elapsed_seconds.count() << endl;
    myHeuristicAlgorithmFile.close();

    string goBack;
    cout << "\nPress key to go back to main panel."<<endl;
    cin >> goBack;
}
