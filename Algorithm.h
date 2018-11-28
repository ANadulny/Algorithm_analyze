#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED
#include <iostream>
#include <vector>

class Algorithm {

		//TODO
		//trzeba bedzie dodac dwa argumenty:
		//table[] i length
		//albo Sticks sticks
		//std::vector<std::vector<int>> combination; // [n, a, b] n liczba powtorzen a pary a i b to warianty budowy bokow

    public:

		//void addPairs(int a, int b); // dodanie pary do wektora
		//void clearPairs(); // czyszczenie wektora par

        int AlgorithmNaive(int table[], int length);
        int AlgorithmMyHeuristic(int table[], int length);

        void quicksort(int tablica[], int p, int r);

};


//Algorithm::Algorithm() { }

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

int searchingTwoSidesOfSquare (int tab[], int length, int position, int searchingSum, int countedElements);
int searchingThreeSticks (int tab[], int length, int position);
int newton(int n, int k);

int Algorithm::AlgorithmMyHeuristic(int table[], int length)
{
    quicksort(table,0,length-1);
    for(int i = 0; i < length; i++)
    {
        std::cout << "[" << i << "]: " << table[i] << " "<< std::endl;
    }

	int sum = 0;
	int first = table[0];
	int counter = 1;
	int tmp;

	for	(int i = 1; i < length - 3; i++) // bo może być warian ze 3 pierwsze liczby tej samej dlugosci
	{
		if(table[i] == first)
			counter++;

		else if(table[i] != first && counter > 1)
		{
			//counter co najmniej = 2
			sum += searchingTwoSidesOfSquare(table, length, i, table[i-1], counter);;
			std::cout<< "Suma: " << sum << std::endl;

			if(counter > 2)
			{
				tmp = searchingThreeSticks (table, length, i);
				sum = sum + tmp * newton(counter, 3);
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

    //gdzies zle zliczanie przypadkow jest

    int i = position, j = length-1;
    int counter = 0;
    int tmp;
    std::vector<int> combination; // [n, a, b]
    //dla przypadku 12,12,4,4,4,4,4,4,4,4,4
    // gdzie searching sum to 12

    if(tab[i] == tab[j] && tab[i] * 2 == searchingSum)
    {
        counter = newton(length - position, 4) * newton(countedElements, 2);
        std::cout << tab[position-1] << " " << tab[position-1] << " " << tab[i] << " " << tab[i] << " " << tab[i] << " " << tab[i];
        std::cout << " the same 6 elements for " << counter << " combination."<<std::endl;
        return counter;
    }

    for( ; i != j, tab[i] >= (int)(searchingSum / 2), tab[j] <= (int)(searchingSum / 2) ; )
    {
        if(tab[i] + tab[j] > searchingSum)
        {
            i++;
            continue;
        }
        else if(tab[i] + tab[j] < searchingSum)
        {
            j--;
            continue;
        }

        else if(tab[i] + tab[j] == searchingSum && tab[i] != tab[j])
        {
            tmp = 1;
            while(tab[i+1] + tab[j] == searchingSum)
            {
                tmp++;
                i++;
            }

            while(tab[i] + tab[j-1] == searchingSum)
            {
                tmp++;
                j--;
            }

            if(combination.empty())
            {
                combination.push_back(tmp);
                combination.push_back(tab[i]);
                combination.push_back(tab[j]);
                i++;
                j--;
            }

            else
            {
                int n,a,b;
                int counterTmp;
                for(int it = 0; it < combination.size(); it++)
                {
                    n = combination[it++];
                    a = combination[it++];
                    b = combination[it++];


                    counterTmp = newton(countedElements, 2) * n * tmp;
                    counter = counter + counterTmp;
                    if(counterTmp > 0)
                        std::cout << tab[position-1] << " " << tab[position-1] << " " << a << " " << b << " " << tab[i] << " " << tab[j] << " the same 6 elements for " << counterTmp << " combination."<<std::endl;
                }

                counterTmp = newton(tmp, 4) * newton(countedElements, 2);
                counter = counter + counterTmp;

                if(counterTmp > 0)
                    std::cout << tab[position-1] << " " << tab[position-1] << " " << tab[i] << " " << tab[i] << " " << tab[i] << " " << tab[i] << " the same 6 elements for " << counterTmp << " combination."<<std::endl;

                combination.push_back(tmp);
                combination.push_back(tab[i]);
                combination.push_back(tab[j]);
                i++;
                j--;
            }

        }

        else // tab[i] + tab[j] == searchingSum && tab[i] == tab[j]
        {


            int theSameElements = j - i + 1;

            int n,a,b;
            int counterTmp;

            for(int it = 0; it < combination.size(); it++)
            {
                n = combination[it++];
                a = combination[it++];
                b = combination[it++];


                counterTmp = newton(countedElements, 2) * n * newton(theSameElements, 2);
                counter = counter + counterTmp;
                if(counterTmp > 0)
                    std::cout << tab[position-1] << " " << tab[position-1] << " " << a << " " << b << " " << tab[i] << " " << tab[j] << " the same 6 elements for " << counterTmp << " combination."<<std::endl;
            }

            counterTmp = newton(tmp, 4) * newton(countedElements, 2);
            counter = counter + counterTmp;

            if(counterTmp > 0)
                std::cout << tab[position-1] << " " << tab[position-1] << " " << tab[i] << " " << tab[i] << " " << tab[i] << " " << tab[i] << " the same 6 elements for " << counterTmp << " combination."<<std::endl;


            break;

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
