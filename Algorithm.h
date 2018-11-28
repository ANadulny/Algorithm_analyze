#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED
#include <iostream>

class Algorithm {

        //Sticks sticks;
		//vector< array<int, 2>>
		// nie moze byc taki wektor
		// zamienic na wektor 2 wymiarowy albo wektor tablicy dwoch intow 
		vector<int> pairs;

    public:
		Algorithm();
        //Algorithm(Sticks sticks);

		void addPairs(int a, int b); // dodanie pary do wektora
		void clearPairs() // czyszczenie wektora par 
		
        int AlgorithmNaive(int table[], int length);
        int AlgorithmMyHeuristic(int table[], int length);

        void quicksort(int tablica[], int p, int r);

};

Algorithm::Algorithm()
{
	//???
	pairs = none;
}

//Algorithm::Algorithm(Sticks stick)
//{
//    sticks = stick;
//}

int Algorithm::AlgorithmNaive(int table[], int length)
{
    if (length < 6) {
        std::cout << "Length is less than 6!" << std::endl;
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
                                    std::cout << tab[i] << " ";
                                std::cout << " (3" << std::endl;
                                std::cout << "MAx elem: "<<max_elem<<"   Counting: " << counting << "   Sum: " << sum << std::endl;
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
                                            std::cout << tab[i] << " ";
                                        std::cout << " (2" << std::endl;
                                        std::cout << "MAx elem: "<<max_elem<<"   Counting: " << counting << "   Sum: " << sum << std::endl;
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

int Algorithm::AlgorithmMyHeuristic(int table[], int length)
{
    quicksort(table,0,length-1);
    for(int i = 0; i < length; i++)
    {
        std::cout << "[" << i << "]: " << table[i] << " "<< std::endl;
    }
	
	int sum = 0;
	int first = table[i];
	int counter = 1;
	int tmp;
	
	for	(int i = 1; i < length - 3; i++) // bo może być warian ze 3 pierwsze liczby tej samej dlugosci
	{
		if(table[i] == first)
			counter++;
		
		else if(table[i] != first && counter > 1)
		{
			//counter co najmniej = 2
			tmp = searchingTwoSidesOfSquare(table, length, i, table[i-1]);
			//tmp zwraca liczbe wariantow zbudowania boku za pomoca 2 liczb tak zeby suma = table[i-1]
			
			// dwa boki mamy zbudowac wiec tmp >= 2
			sum = sum + newton(tmp, 2) * newton(counter, 2); 
			std::cout<< "Suma: " << sum <<std::endl;
			// TODO
			// Petla wypisujaca z vektora pary liczb
			// Nastepnie 
			// z uwzglednieniem 2 liczb maximum - table[i-1]
			// problem z wypisywaniem kobinacji 6 liczb
			
			if(counter > 2)
			{	
				tmp = searchingThreeSticks (table, length, i);
				sum = sum + tmp * newton(counter, 3);
				std::cout<< "Suma: " << sum <<std::endl;
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
	number = 1;
	for(int i = 1; i <= k; i++)
		number = number * ( n - i +1 ) / i;
	return number;
}

//zwraca liczbe wariantow gdzie za pomoca 2 liczb mozna otrzymac sume searchingSum
int searchingTwoSidesOfSquare (int tab[], int length, int position, int searchingSum)
{
    //TODO
	// wstawiamy 
    return 1;
}

int searchingThreeSticks (int tab[], int length, int position)
{
    //TODO
	//
    return 2;
}
#endif // ALGORITHM_H_INCLUDED
