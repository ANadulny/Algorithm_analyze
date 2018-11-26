#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED
#include <iostream>

class Algorithm {

        //Sticks sticks

    public:
        //Algorithm(int l, int tab[]);

        int AlgorithmNaive(int table[], int length);
        int AlgorithmMyHeuristic(int table[], int length);

        void quicksort(int tablica[], int p, int r);

};

//Algorithm::Algorithm(int l, int tab[] )
//{
//    length = l;
//    table = tab;
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

    //TODO

    return length;
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

int searchingTwoSidesOfSquare (int tab[], int length, int position, int searchingSum)
{
    //TODO
    return 1;
}

int searchingThreeSticks (int tab[], int length, int position)
{
    //TODO
    return 2;
}
#endif // ALGORITHM_H_INCLUDED
