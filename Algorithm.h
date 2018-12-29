/*
@title Zadanie 9: Znajdowanie i zliczanie kombinacji takich 6 elementow (z tablicy S elementowej liczb naturalnych mniejszych badz rownych S) za pomocą ktorych mozna zbudowac kwadrat.
@author Adrian Nadulny
index: 283706
*/
#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>

class Algorithm
{

    int length;
    int *algorithmTable;
    std::vector<int> combination; // [n, a, b]

public:
    Algorithm( Sticks& stick);
    ~Algorithm();
    int algorithmNaive( std::ofstream &myFile);
    int algorithmMyHeuristic( std::ofstream &myFile);

private:
    void quicksort(int table[], int p, int r);
    int searchingTwoSidesOfSquare ( int position, int counterRepeatingNumber, std::ofstream &myFile);
    int searchingThreeSticks ( int position, int counterRepeatingNumber, std::ofstream &myFile);
};


Algorithm::Algorithm( Sticks &stick)
{
    length = stick.getStickNumber();
    algorithmTable = stick.getNewStickTable();
}

Algorithm::~Algorithm()
{
    delete []algorithmTable;
    algorithmTable = nullptr;
}

int Algorithm::algorithmNaive( std::ofstream &myFile)
{
    for( int i = 0; i < length; i++ )
        myFile << "[" << i << "]: " << algorithmTable[i] << "\n";

    myFile << "===========================================\n";
    if (length < 6 )
    {
        myFile << "Length is less than 6!\n";
        return 0;
    }

    int squaresCounter = 0;
    int table[6];

    for( int i1 = 0; i1 < length-5; i1++ )
    {
        table[0] = algorithmTable[i1];
        for( int i2 = 1 + i1; i2 < length-4; i2++ )
        {
            table[1] = algorithmTable[i2];
            for( int i3 = 1 + i2; i3 < length-3; i3++ )
            {
                table[2] = algorithmTable[i3];
                for( int i4 = 1 + i3; i4 < length-2; i4++ )
                {
                    table[3] = algorithmTable[i4];
                    for( int i5 = 1 + i4; i5 < length-1; i5++ )
                    {
                        table[4] = algorithmTable[i5];
                        for( int i6 = 1 + i5; i6 < length; i6++ )
                        {
                            table[5] = algorithmTable[i6];
                            int counterLargestNumber = 1;
                            int maxElement;
                            int sum = 0;

                            for( int i = 0; i < 6; i++ ) //searching the max number
                            {
                                sum += table[i];

                                if( i == 0)
                                {
                                    maxElement = table[i];
                                    continue;
                                }
                                if( table[i] > maxElement )
                                {
                                    maxElement = table[i];
                                    counterLargestNumber = 1;
                                }
                                else if( table[i] == maxElement )
                                    counterLargestNumber++;
                            }

                            if( counterLargestNumber == 3 && sum == (maxElement * 4) )
                            {
                                squaresCounter++;

                                for(int i = 0; i < 6; i++)
                                    myFile << table[i] << " ";

                                myFile << "\n";
                            }

                            else if( counterLargestNumber == 2 && sum == (maxElement * 4) )
                            {
                                int j = 0;
                                for( int i = 0; i < 6; i++ )
                                {
                                    if( table[i] < maxElement )
                                    {
                                        j = i;
                                        break;
                                    }
                                }

                                int pom = table[j++];
                                for( ; j < 6; j++ )
                                {
                                    if( table[j] < maxElement && table[j] + pom == maxElement )
                                    {
                                        squaresCounter++;

                                        for( int i = 0; i < 6; i++ )
                                            myFile << table[i] << " ";

                                        myFile << "\n";
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
    return squaresCounter;
}

int Algorithm::algorithmMyHeuristic( std::ofstream &myFile )
{
    quicksort( algorithmTable, 0, length - 1 );

    for( int i = 0; i < length; i++ )
        myFile << "[" << i << "]: " << algorithmTable[i] << " \n";

    myFile << "===========================================\n";
    if( length < 6 )
    {
        myFile << "Length is less than 6!\n";
        return 0;
    }

    int squaresCounter = 0;
    int counterRepeatingNumber = 1;

    for( int i = 1; i < length - 3; i++ )   // to build square: the last 3 numbers must be lower than algorithmTable[length - 4]
    {
        if( algorithmTable[i] == algorithmTable[i-1] )
        {
            counterRepeatingNumber++;
            continue;
        }
        else if( algorithmTable[i] != algorithmTable[i-1] && counterRepeatingNumber > 1 )
        {
            squaresCounter += searchingTwoSidesOfSquare( i, counterRepeatingNumber, myFile );
            squaresCounter += searchingThreeSticks( i, counterRepeatingNumber, myFile );
        }

        counterRepeatingNumber = 1;
    }
    return squaresCounter;
}

int partition( int table[], int p, int r )
{
    int x = table[p];
    int i = p, j = r, w;
    while( true )
    {
        while( table[j] < x )
            j--;

        while( table[i] > x )
            i++;

        if( i < j )
        {
            w = table[i];
            table[i] = table[j];
            table[j] = w;
            i++;
            j--;
        }
        else
            return j;
    }
}

void Algorithm::quicksort( int table[], int p, int r )
{
    int q;
    if( p < r )
    {
        q = partition( table, p, r );
        quicksort( table, p, q );
        quicksort( table, q + 1, r );
    }
}

int newton( int n, int k )
{
    int number = 1;
    for( int i = 1; i <= k; i++ )
        number = number * ( n - i + 1 ) / i;
    return number;
}

//tmpi - counter of repetition from the left
//tmpj - counter of repetition from the right
int Algorithm::searchingTwoSidesOfSquare ( int position, int counterRepeatingNumber, std::ofstream &myFile )
{
    int squaresCounter = 0;
    int countedElementsCombination = newton( counterRepeatingNumber, 2 );
    combination.clear(); // [n, a, b]
    int i = position, j = length - 1;
    int tmpi, tmpj, tmpNumberOfCombination;

    while( algorithmTable[i] >= (int)(algorithmTable[position-1] / 2) && algorithmTable[j] <= (int)(algorithmTable[position-1] / 2) )
    {
        if( algorithmTable[i] + algorithmTable[j] > algorithmTable[position-1] )
        {
            i++;
            continue;
        }
        else if( algorithmTable[i] + algorithmTable[j] < algorithmTable[position-1] )
        {
            j--;
            continue;
        }

        tmpi = 1;
        while( i != position - 1 && algorithmTable[i+1] + algorithmTable[j] == algorithmTable[position-1] )
        {
            tmpi++;
            i++;
        }

        if( i != j)
        {
            tmpj = 1;
            while( algorithmTable[i] + algorithmTable[j-1] == algorithmTable[position-1] )
            {
                tmpj++;
                j--;
            }
            tmpNumberOfCombination = tmpj * tmpi;
        }

        else
            tmpNumberOfCombination = tmpi * (tmpi - 1) / 2;

        int n, a, b;
        int counterTmp;
        for( unsigned int it = 0; it < combination.size(); )
        {
            n = combination[it++];
            a = combination[it++];
            b = combination[it++];

            counterTmp = countedElementsCombination * n * tmpNumberOfCombination ;
            squaresCounter += counterTmp;
            //if( counterTmp > 0 )
                myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << a << " " << b << " " << algorithmTable[i]
                       << " " << algorithmTable[j] << " the same 6 elements for " << counterTmp << " combination.\n";
        }

        if( i == j )
            counterTmp = countedElementsCombination * newton(tmpi, 4);
        else
            counterTmp = countedElementsCombination * newton(tmpi, 2) * newton(tmpj, 2);

        squaresCounter += counterTmp;
        if( counterTmp > 0 )
            myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " " << algorithmTable[i]
                   << " " << algorithmTable[j] << " " << algorithmTable[j] << " the same 6 elements for " << counterTmp << " combination.\n";

        combination.push_back(tmpNumberOfCombination);
        combination.push_back(algorithmTable[i++]);
        combination.push_back(algorithmTable[j--]);
    }
    return squaresCounter;
}

int Algorithm::searchingThreeSticks ( int position, int counterRepeatingNumber, std::ofstream &myFile )
{
    if( counterRepeatingNumber < 3 )
        return 0;

    int squaresCounter = 0;
    int countedElementsCombination = newton( counterRepeatingNumber, 3 );
    int tmpi, tmpj, tmpk;
    int counterTmp;

    for ( int i = position; i < length - 2; i++ )
    {
        int searchingSum = algorithmTable[position-1] - algorithmTable[i];

        tmpi = 1;
        while( i != position - 1 && algorithmTable[i] == algorithmTable[i+1] )
        {
            tmpi++;
            i++;
        }

        int k = tmpi > 1 ? i : i + 1;
        int j = length - 1;
        while( algorithmTable[k] >= (int)(searchingSum / 2) && algorithmTable[j] <= (int)(searchingSum / 2) )
        {
            if(algorithmTable[k] + algorithmTable[j] > searchingSum)
                k++;

            else if( algorithmTable[k] + algorithmTable[j] < searchingSum )
                j--;

            else
            {
                tmpk = 1;
                while( k != position - 1 && algorithmTable[k] == algorithmTable[k+1] )
                {
                    tmpk++;
                    k++;
                }
                tmpj = 1;
                while( j != k && algorithmTable[j-1] == algorithmTable[j] )
                {
                    j--;
                    tmpj++;
                }

                if( i == j && tmpi > 2 ) // k == j == i
                    counterTmp = countedElementsCombination * newton(tmpi, 3);

                else if( i == k && i != j )
                    counterTmp = countedElementsCombination * newton(tmpi, 2) * tmpj;

                else if( k == j && tmpk > 1 )
                    counterTmp = countedElementsCombination * tmpi * newton(tmpk, 2);

                else if( i != k && k != j )
                    counterTmp = countedElementsCombination * tmpi * tmpj * tmpk;

                else
                {
                    k++;
                    j--;
                    continue;
                }

                myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " ";
                myFile << algorithmTable[k++] << " " << algorithmTable[j--] << " the same 6 elements for " << counterTmp << " combination.\n";
                squaresCounter += counterTmp;
            }
        }
    }
    return squaresCounter;
}
#endif // ALGORITHM_H_INCLUDED
