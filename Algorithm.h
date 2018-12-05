#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>

class Algorithm {


		//std::vector<std::vector<int>> combination; // [n, a, b] n liczba powtorzen a pary a i b to warianty budowy bokow

        // do ogarniecia
        //Sticks sticks;


    public:
        //Algorithm(const Sticks& sticks);

        void setMyFile(std::ofstream& file);
        int AlgorithmNaive(int table[], int length, std::ofstream& myFile);
        int AlgorithmMyHeuristic(int table[], int length);

        void quicksort(int tablica[], int p, int r);
        //~Algorithm();
};
/*
Algorithm::Algorithm(const Sticks& stick)
{
    sticks = stick;
    //this->table = table;
}*/

int Algorithm::AlgorithmNaive(int table[], int length, std::ofstream& myFile)
{
    for ( int i = 0; i < length; i++ )
        myFile << "[" << i << "]: " << table[i] << "\n";

    if (length < 6) {
        myFile << "Length is less than 6!\n";
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

                                for(int i = 0; i < 6; i++)
                                    myFile << tab[i] << " ";

                                myFile << "\n";
                                myFile << "MAx elem: " << max_elem << "   Counting: " << counting << "   Sum: " << sum << "\n";
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

                                        for(int i = 0; i < 6; i++)
                                            myFile << tab[i] << " ";

                                        myFile << "\n";
                                        myFile << "MAx elem: " << max_elem << "   Counting: " << counting << "   Sum: " << sum << "\n";
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

int searchingTwoSidesOfSquare (int tab[], int length, int position, int searchingSum, int countedElements);
int searchingThreeSticks (int tab[], int length, int position);
int newton(int n, int k);

int Algorithm::AlgorithmMyHeuristic(int table[], int length)
{
    quicksort(table, 0, length-1);
    for(int i = 0; i < length; i++)
    {
        std::cout << "[" << i << "]: " << table[i] << " "<< std::endl;
    }

	int sum = 0;
	int first = table[0];
	int counter = 1;

	for	(int i = 1; i < length - 3; i++) // bo może być warian ze 3 pierwsze liczby tej samej dlugosci
	{
		if(table[i] == first)
			counter++;

		else if(table[i] != first && counter > 1)
		{
			//counter co najmniej = 2
			sum += searchingTwoSidesOfSquare(table, length, i, table[i-1], counter);
			std::cout<< "Suma: " << sum << std::endl;

			if(counter > 2)
			{
				sum = sum + searchingThreeSticks (table, length, i) * newton(counter, 3);
				std::cout<< "Suma: " << sum << std::endl;
				// TODO
				// Petla wypisujaca z vektora pary liczb
			}

			counter = 1;
			first = table[i];
		}

		else // table[i]!=first && counter == 1
		{
			first = table[i];
		}
	}

    return sum;
}

int partition(int tablica[], int p, int r)
{
    int x = tablica[p];
    int i = p, j = r, w;
    while (true)
    {
        while (tablica[j] < x)
            j--;

        while (tablica[i] > x)
            i++;

        if (i < j)
        {
            w = tablica[i];
            tablica[i] = tablica[j];
            tablica[j] = w;
            i++;
            j--;
        }

        else
            return j;
    }
}

void Algorithm::quicksort(int tablica[], int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(tablica,p,r);
        quicksort(tablica, p, q);
        quicksort(tablica, q+1, r);
    }
}

int newton(int n, int k)
{
	int number = 1;
	for(int i = 1; i <= k; i++)
		number = number * ( n - i +1 ) / i;
	return number;
}

//zwraca liczbe wariantow gdzie za pomoca 2 liczb mozna otrzymac sume searchingSum
int searchingTwoSidesOfSquare (int tab[], int length, int position, int searchingSum, int countedElements)
{
    int i = position, j = length - 1;
    int counter = 0;
    int tmpi,tmpj,tmp;
    std::vector<int> combination; // [n, a, b]

    /*
    if(tab[i] == tab[j] && tab[i] * 2 == searchingSum)
    {
        counter = newton(length - position, 4) * newton(countedElements, 2);
        std::cout << tab[position-1] << " " << tab[position-1] << " " << tab[i] << " " << tab[i] << " " << tab[i] << " " << tab[i];
        std::cout << " the same 6 elements for " << counter << " combination."<<std::endl;
        return counter;
    }*/

    while( i != j && tab[i] >= (int)(searchingSum / 2) && tab[j] <= (int)(searchingSum / 2) )
    {
        if(tab[i] + tab[j] > searchingSum)
            i++;

        else if(tab[i] + tab[j] < searchingSum)
            j--;

        else //if(tab[i] + tab[j] == searchingSum )
        {
            tmpi = 1;
            while(tab[i+1] + tab[j] == searchingSum)
            {
                tmpi++;
                i++;
            }

            if( i != j)
            {
                tmpj = 1;
                while(tab[i] + tab[j-1] == searchingSum)
                {
                    tmpj++;
                    j--;
                }
                tmp = tmpj * tmpi;
            }

            else
            {
                tmp = tmpi * (tmpi - 1) / 2;
            }
            //tmp - ile wariantow danego typu pojawilo sie
            //tmpi - ile takich samych liczb z gory pojawilo sie
            //tmpj - ile takich samych liczb z dolu pojawilo sie

            if(combination.empty())
            {
                if(i == j)
                    counter = newton(countedElements, 2) * newton(tmpi, 4);
                else
                    counter = newton(countedElements, 2) * newton(tmpi, 2) * newton(tmpj, 2);

                if(counter > 0)
                {
                    std::cout << tab[position-1] << " " << tab[position-1] << " " << tab[i] << " " << tab[i] << " " << tab[j] << " " << tab[j] << " the same 6 elements for " << counter << " combination."<<std::endl;
                }

                combination.push_back(tmp);
                combination.push_back(tab[i]);
                combination.push_back(tab[j]);
                i++;
            }

            else
            {
                int n, a, b;
                int counterTmp;
                for(unsigned int it = 0; it < combination.size();) // wariant gdzie 1 i 2 liczba to max, 3 i 4 z wektora wzieta i 5 oraz 6 wyliczona w tej iteracji
                {
                    n = combination[it++];
                    a = combination[it++];
                    b = combination[it++];

                    counterTmp = newton(countedElements, 2) * n * tmp ;
                    counter = counter + counterTmp;
                    std::cout << tab[position-1] << " " << tab[position-1] << " " << a << " " << b << " " << tab[i] << " " << tab[j] << " the same 6 elements for " << counterTmp << " combination."<<std::endl;

                }

                counterTmp = 0;
                if(i == j)
                    counterTmp = newton(countedElements, 2) * newton(tmpi, 4);

                else
                    counterTmp = newton(countedElements, 2) * newton(tmpi, 2) * newton(tmpj, 2);

                counter = counter + counterTmp;
                if(counterTmp > 0)
                    std::cout << tab[position-1] << " " << tab[position-1] << " " << tab[i] << " " << tab[i] << " " << tab[j] << " " << tab[j] << " the same 6 elements for " << counterTmp << " combination."<<std::endl;

                combination.push_back(tmp);
                combination.push_back(tab[i]);
                combination.push_back(tab[j]);
                i++; // ewentualnie j-- mozna dodac i sprawdzic czy cos szybciej dziala
            }
        }
    }
    combination.clear();
    return counter;
}

int searchingThreeSticks (int tab[], int length, int position)
{
    //TODO
    int counter = 0;
	//for(int i = position)
    return counter;
}
#endif // ALGORITHM_H_INCLUDED
