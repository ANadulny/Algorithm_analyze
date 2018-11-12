#include <iostream>
#include <chrono>
#include <random>
#include "Sticks.h"

using namespace std;

void UI();

int AlgorithmNaive(int table[], int lengt);

int main()
{
    int stickNumber;
    UI();
    cin >> stickNumber;

    // testing
    cout << "Sticks number: " << stickNumber << endl;

    Sticks sticks(stickNumber);
    sticks.generateStickTable();

    int stickTable[sticks.getStickNumber()];
    //testing
    for ( int i = 0; i < sticks.getStickNumber(); i++ ) {
        cout << i << ": " << *(sticks.getStickTable()+i) << endl;
        stickTable[i] = *(sticks.getStickTable()+i);
    }

    //Testing
    //int table [10] = {6,3,2,1,6,3,3,9,8,3};
    //int table [7] = {6,3,6,3,3,7,3};
    //int table [7] = {7,3,3,6,3,3,6};
    //int table [7] = {5,2,1,5,1,5,2};
    //for ( int i = 0; i < 7; i++ ) {
    //    cout << i << ": " << table[i] << endl;
    //}
    //cout << AlgorithmNaive(table, 7 ) << ": Squares number" << endl;

    cout << "===========================================" << endl;
    cout << AlgorithmNaive(stickTable, sticks.getStickNumber() ) << ": Squares number" << endl;
    return 0;
}

void UI()
{
    cout << "Please enter the number of sticks:" << endl;
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

                            //Testing
                            //    for(int i = 0; i < 6; i++)
                            //                cout << tab[i] << " ";
                            //            cout << endl;

                            // Testing
                            //cout << "MAx elem: "<<max_elem<<"   Counting: " << counting << "   Sum: " << sum << endl;

                            // i don't care
                            //if(counting > 3 || counting < 2)
                            //    continue;

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
