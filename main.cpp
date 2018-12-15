/*
@title Zadanie 9: Znajdowanie i zliczanie kombinacji takich 6 elementow (z tablicy S elementowej liczb naturalnych mniejszych badz rownych S) za pomocą ktorych mozna zbudowac kwadrat.
@author Adrian Nadulny
index: 283706
*/
#include <iostream>
#include <chrono>
#include <random>
#include <chrono>
#include <fstream>
#include "Sticks.h"
#include "Algorithm.h"

using namespace std;

void UI();
int  newStickNumber();
void optionScreen(Sticks &sticks);
void changeSticksNumber(Sticks &sticks);
void generateStickTableElements(Sticks &sticks);
void showStickTableElements(Sticks &sticks);
void generateOwnStickTableElements(Sticks &sticks);
void viewAlgorithmsTimeMeasure(Sticks &sticks);
void algorithmsTimeMeasure(Algorithm &algorithm, string fileName, int p);

int main()
{
    UI();
    return 0;
}

void UI()
{
    cout << "Please enter the number of sticks: " << endl;

    int stickNumber = newStickNumber();

    //Poczatek wypelniania tablicy S elementowej
    Sticks sticks( stickNumber);
    sticks.generateStickTable();

    int decision;

    while(1)
    {
        system("clear");
        optionScreen(sticks);
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
            changeSticksNumber( sticks );
            break;
        case 2:
            generateStickTableElements(sticks);
            break;
        case 3:
            generateOwnStickTableElements(sticks);
            break;
        case 4:
            viewAlgorithmsTimeMeasure(sticks);
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
    do
    {
        cin >> stickNumber;
        if(cin.fail() )
        {
            cin.clear();
            cin.ignore(150, '\n');
        }
    }
    while ( stickNumber < 6 );
    return stickNumber;
}

void optionScreen (Sticks &sticks)
{
    cout << "Current S value: " << sticks.getStickNumber() << endl;
    cout << "Write correct number:" << endl;
    cout << "[1] Change sticks number S:" << endl;
    cout << "[2] Generate random value for sticks table." << endl;
    cout << "[3] Generate own sticks table." << endl;
    cout << "[4] Measure time of algorithms." << endl;
    cout << "[5] Show elements from stick table." << endl;
    cout << "[6] End program." << endl;
}

void changeSticksNumber(Sticks &sticks)
{
    system("clear");
    cout << "Write new sticks number S:" << endl;
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
        cout << "[" << i << "]:" << *(sticks.getStickTable() + i) <<"  ";

    string goBack;
    cout << "\nPress key to go back to main panel."<<endl;
    cin >> goBack;
}

void generateOwnStickTableElements(Sticks &sticks)
{
    int newElem;
    for( int i = 0; i < sticks.getStickNumber(); i++)
    {
        system("clear");
        cout << "Write: " << sticks.getStickNumber() - i << " new elements." << endl;
        cout << "Element can not be more than: " << sticks.getStickNumber() << endl;
        do
        {
            cin >> newElem;
            if(cin.fail() )
            {
                cin.clear();
                cin.ignore(150, '\n');
            }
        }
        while ( newElem < 1 || newElem > sticks.getStickNumber() );
        *(sticks.getStickTable() + i) = newElem;
    }
}

void viewAlgorithmsTimeMeasure(Sticks &sticks)
{
    system("clear");
    Algorithm algorithm(sticks);

    cout << "[1] NaiveAlgorithm" << endl;
    string naiveAlgorithmFile = "naiveAlgorithm.txt";
    algorithmsTimeMeasure(algorithm, naiveAlgorithmFile, 1);

    cout << "[2] AlgorithmMyHeuristic" << endl;
    string myHeuristicAlgorithmFile = "myHeuristicAlgorithm.txt";
    algorithmsTimeMeasure(algorithm, myHeuristicAlgorithmFile, 2);

    string goBack;
    cout << "\nPress key to go back to main panel." << endl;
    cin >> goBack;
}

void algorithmsTimeMeasure(Algorithm &algorithm, string fileName, int p)
{
    int squaresNumber;
    ofstream myFile;
    myFile.open(fileName);

    if(p == 1)
        myFile << "Naive Algorithm:\n";
    else
        myFile << "My Heuristic Algorithm:\n";

    myFile << "===========================================\n";
    cout << "===========================================" << endl;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    if(p == 1)
        squaresNumber = algorithm.AlgorithmNaive( myFile );
    else
        squaresNumber = algorithm.AlgorithmMyHeuristic( myFile );

    cout << squaresNumber << ": Squares number" << endl;
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "===========================================" << endl;
    cout << "Algorithm time: " << elapsed_seconds.count() << endl;
    cout << endl;
    myFile << "Squares number: " << squaresNumber << "\n";
    myFile << "===========================================\n";
    myFile << "Algorithm time: " << elapsed_seconds.count() << "\n";
    myFile.close();
}
