#include <iostream>
#include <chrono>
#include <random>
#include <chrono>
#include "Sticks.h"

#define SLEEP_TIME 500

using namespace std;

void UI();

int AlgorithmNaive(int table[], int lengt);

int main()
{
    UI();
    return 0;
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

void screen (Sticks &sticks)
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

void screen1(Sticks &sticks)
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

void screen2(Sticks &sticks)
{
    // albo od razu mierzone są dane dla jednego i drugiego algosa
    system("clear");
    cout<<"Choose type of algorithm:"<<endl;
    cout<<"[1] AlgorithmMyHeuristic"<<endl;
	cout<<"[2] NaiveAlgorithm" <<endl;

    string a;
    cin >> a;
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
        screen( sticks );
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
                screen1( sticks );
                break;
            case 2:
                generateStickTableElements(sticks);
                break;
            case 3:
                generateOwnStickTableElements(sticks);
                break;
            case 4:
                screen2(sticks);
                break;
            case 5:
                showStickTableElements(sticks);
                break;
            default:
                return;
        }

    }

    //int stickTable[sticks.getStickNumber()];

    //testing
    //for ( int i = 0; i < sticks.getStickNumber(); i++ ) {
    //    cout << i << ":" << *(sticks.getStickTable()+i) <<"; ";
    //    stickTable[i] = *(sticks.getStickTable()+i);
    //}
    //cout << endl;
    /*
    cout << "===========================================" << endl;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    cout << AlgorithmNaive(stickTable, sticks.getStickNumber() ) << ": Squares number" << endl;
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "===========================================" << endl;
    cout << "Algorithm time: " << elapsed_seconds.count() << endl;
    */
}

int AlgorithmNaive(int table[], int length)
{
    if (length < 6) {
        cout << "Length is less than 6!" << endl;
        return 0;
    }

    int counter = 0;
    int tab[6];

    for(int i1 = 0; i1 < length-5; i1++)
    {
        tab[0] = table[i1];
        int max_elem;
        for(int i2 = 1 + i1; i2 < length-4; i2++)
        {
            tab[1] = table[i2];
            for(int i3 = 1 + i2; i3 < length-3; i3++)
            {
                tab[2] = table[i3];
                for(int i4 = 1 + i3; i4 < length-2; i4++)
                {
                    tab[3] = table[i4];
                    for(int i5 = 1 + i4; i5 < length-1; i5++)
                    {
                        tab[4] = table[i5];
                        for(int i6 = 1 + i5; i6 < length; i6++)
                        {
                            int counting = 1;
                            tab[5] = table[i6];
                            int sum = 0;
                            for(int i = 0; i < 6; i++) //searching the max number
                            {
                                sum += tab[i];

                                if(i == 0)
                                {
                                    max_elem = tab[i];
                                    continue;
                                }

                                if(tab[i] > max_elem)
                                {
                                    max_elem = tab[i];
                                    counting = 1;
                                }
                                else if(tab[i] == max_elem)
                                    counting++;
                            }

                            if (counting == 3 && sum == (max_elem * 4)) // the largest 3 sticks have the same number
                            {
                                counter++;

                                //Testing
                                for(int i = 0; i < 6; i++)
                                    cout << tab[i] << " ";
                                cout << " (3" << endl;
                                cout << "MAx elem: "<<max_elem<<"   Counting: " << counting << "   Sum: " << sum << endl;
                            }

                            else if (counting == 2 && sum == (max_elem * 4)) // the largest 2 sticks have the same number
                            {
                                int j = 0;
                                for(int i = 0; i < 6; i++)
                                {
                                    if(tab[i] < max_elem)
                                    {
                                        j = i;
                                        break;
                                    }
                                }
                                int pom = tab[j++];
                                for(; j < 6; j++)
                                {
                                    if(tab[j] < max_elem && tab[j] + pom == max_elem)
                                    {
                                        counter++;

                                        //Testing
                                        for(int i = 0; i < 6; i++)
                                            cout << tab[i] << " ";
                                        cout << " (2" << endl;
                                        cout << "MAx elem: "<<max_elem<<"   Counting: " << counting << "   Sum: " << sum << endl;
                                        break;
                                    }

                                }

                            }
                        }
                    }
                }
            }
        }
    }

    return counter;
}
