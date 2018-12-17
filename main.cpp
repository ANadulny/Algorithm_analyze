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
#include <fstream>
#include <iomanip>
#include "Sticks.h"
#include "Algorithm.h"

using namespace std;

void UI();
int  getNumber();
int  getStickNumber();
void optionScreen(Sticks &sticks);
void changeSticksNumber(Sticks &sticks);
void generateStickTableElements(Sticks &sticks);
void showStickTableElements(Sticks &sticks);
void generateOwnStickTableElements(Sticks &sticks);
void viewAlgorithmsTimeMeasure(Sticks &sticks);
void algorithmsTimeMeasure(Algorithm &algorithm, string fileName);
double algorithmsTimeMeasure(Algorithm &algorithm, string fileName, int p);
void generateTimeMeasureResults(Sticks &sticks);
void saveTimeMeasureData(ofstream &myFile, int stickNumberTab[], double algorithmTimes[][5], int length);
int main()
{
    UI();
    return 0;
}

void UI()
{
    cout << "Please enter the number of sticks: " << endl;

    int stickNumber = getStickNumber();

    //Poczatek wypelniania tablicy S elementowej
    Sticks sticks(stickNumber);
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

        if(decision < 1 || decision > 7)
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
        case 6:
            generateTimeMeasureResults(sticks);
            break;
        default:
            return;
        }
    }
}

int getNumber()
{
    int number;
    do
    {
        cin >> number;
        if(cin.fail() )
        {
            cin.clear();
            cin.ignore(150, '\n');
        }
    }
    while ( number < 1 );
    return number;
}

int getStickNumber()
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
    cout << "[6] Generate for random data CSV file." << endl;
    cout << "[7] End program." << endl;
}

void changeSticksNumber(Sticks &sticks)
{
    system("clear");
    cout << "Write new sticks number S:" << endl;
    int newSticksNumber = getStickNumber();
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
        cout << "[" << i << "]:" << *(sticks.getStickTable() + i) <<endl;

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
    string naiveAlgorithmFile = "naiveAlgorithm";
    algorithmsTimeMeasure(algorithm, naiveAlgorithmFile);

    cout << "[2] AlgorithmMyHeuristic" << endl;
    string myHeuristicAlgorithmFile = "myHeuristicAlgorithm";
    algorithmsTimeMeasure(algorithm, myHeuristicAlgorithmFile);

    string goBack;
    cout << "\nPress key to go back to main panel." << endl;
    cin >> goBack;
}

void algorithmsTimeMeasure(Algorithm &algorithm, string fileName)
{
    int squaresNumber;
    ofstream myFile;

    myFile.open(fileName + "/" + fileName + ".txt");

    if(fileName == "naiveAlgorithm")
        myFile << "Naive Algorithm:\n";
    else
        myFile << "My Heuristic Algorithm:\n";

    myFile << "===========================================\n";
    cout << "===========================================" << endl;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    if(fileName == "naiveAlgorithm")
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

double algorithmsTimeMeasure(Algorithm &algorithm, string fileName, int p)
{
    int squaresNumber;
    ofstream myFile;
    myFile.open(fileName + "/" + fileName + to_string(p) + ".txt");

    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    if(fileName == "naiveAlgorithm")
        squaresNumber = algorithm.AlgorithmNaive( myFile );
    else
        squaresNumber = algorithm.AlgorithmMyHeuristic( myFile );
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    myFile << "Squares number: " << squaresNumber << "\n";
    myFile << "===========================================\n";
    myFile << "Algorithm time: " << elapsed_seconds.count() << "\n";
    myFile.close();

    return elapsed_seconds.count();
}


void generateTimeMeasureResults(Sticks &sticks)
{
    system("clear");
    cout << "Write number of measurements: " << endl;
    int measureNumber = getNumber();

    int stickNumberForIteration[measureNumber];
    double naiveAlgTimes[measureNumber][5];
    double myHeuristicAlgTimes[measureNumber][5];
    for(int i = 0; i < measureNumber; i++)
    {
        system("clear");
        cout << "Please enter " << measureNumber - i << " numbers of sticks: " << endl;
        stickNumberForIteration[i] = getStickNumber();
    }

    system("clear");
    cout << "Please wait for a while." << endl;
    for(int i = 0 ; i < measureNumber; i++)
    {
        sticks.setStickNumber(stickNumberForIteration[i] );
        string naiveAlgorithmFile = "naiveAlgorithm";
        string myHeuristicAlgorithmFile = "myHeuristicAlgorithm";

        for(int j = 0; j < 5; j++)
        {
            Algorithm algorithm(sticks);
            naiveAlgTimes[i][j] = algorithmsTimeMeasure(algorithm, naiveAlgorithmFile, i);
            myHeuristicAlgTimes[i][j] = algorithmsTimeMeasure(algorithm, myHeuristicAlgorithmFile, i);
            sticks.generateStickTable();
        }
    }

    ofstream naiveFile;
    naiveFile.open("naiveAlgorithm/NaiveAlgorithmTimeMeasures.csv");
    saveTimeMeasureData(naiveFile, stickNumberForIteration, naiveAlgTimes, measureNumber);
    naiveFile.close();

    ofstream myHeuristicFile;
    myHeuristicFile.open("myHeuristicAlgorithm/MyHeuristicAlgorithmTimeMeasures.csv");
    saveTimeMeasureData(myHeuristicFile, stickNumberForIteration, myHeuristicAlgTimes, measureNumber);
    myHeuristicFile.close();

}

void saveTimeMeasureData(ofstream &myFile, int stickNumberTab[], double algorithmTimes[][5], int length)
{
    myFile << "Liczba S,\t\tCzasy dla poszczegolnych wywolan programu,\t\tSrednia wszystkich wykonan\n";
    for(int i = 0 ; i < length; i++)
    {
        myFile << stickNumberTab[i] << ",";
        double average = 0;
        for(int j = 0; j < 5; j++)
        {
            average += algorithmTimes[i][j];
            myFile << algorithmTimes[i][j] << ",";
        }
        myFile << setprecision(8) << (average / 5) << "\n";
    }
}
