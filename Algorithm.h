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

class Algorithm {

        int length;
        int *algorithmTable;
        std::vector<int> combination; // [n, a, b]

    public:
        Algorithm(Sticks& stick);
        ~Algorithm();
        int AlgorithmNaive( std::ofstream &myFile);
        int AlgorithmMyHeuristic( std::ofstream &myFile);

    private:
        void quicksort(int tablica[], int p, int r);
        int searchingTwoSidesOfSquare ( int position, int countedElements, std::ofstream &myFile);
        int searchingThreeSticks (int position, int countedElements, std::ofstream &myFile);
};


Algorithm::Algorithm( Sticks &stick) {
    length = stick.getStickNumber();
    algorithmTable = stick.getNewStickTable();
}

Algorithm::~Algorithm() {
    delete []algorithmTable;
    algorithmTable = nullptr;
}

int Algorithm::AlgorithmNaive( std::ofstream &myFile) {
    for( int i = 0; i < length; i++ )
        myFile << "[" << i << "]: " << algorithmTable[i] << "\n";

    myFile << "===========================================\n";
    if (length < 6) {
        myFile << "Length is less than 6!\n";
        return 0;
    }

    int counter = 0;
    int tab[6];

    for( int i1 = 0; i1 < length-5; i1++) {
        tab[0] = algorithmTable[i1];
        int max_elem;
        for( int i2 = 1 + i1; i2 < length-4; i2++) {
            tab[1] = algorithmTable[i2];
            for( int i3 = 1 + i2; i3 < length-3; i3++) {
                tab[2] = algorithmTable[i3];
                for( int i4 = 1 + i3; i4 < length-2; i4++) {
                    tab[3] = algorithmTable[i4];
                    for( int i5 = 1 + i4; i5 < length-1; i5++) {
                        tab[4] = algorithmTable[i5];
                        for( int i6 = 1 + i5; i6 < length; i6++) {
                            int counting = 1;
                            tab[5] = algorithmTable[i6];
                            int sum = 0;
                            //searching the max number
                            for( int i = 0; i < 6; i++) {
                                sum += tab[i];

                                if(i == 0) {
                                    max_elem = tab[i];
                                    continue;
                                }

                                if(tab[i] > max_elem) {
                                    max_elem = tab[i];
                                    counting = 1;
                                }
                                else if(tab[i] == max_elem)
                                    counting++;
                            }
                            // the largest 3 sticks have the same number
                            if (counting == 3 && sum == (max_elem * 4)) {
                                counter++;

                                for(int i = 0; i < 6; i++)
                                    myFile << tab[i] << " ";

                                myFile << "\n";
                            }
                            // the largest 2 sticks have the same number
                            else if (counting == 2 && sum == (max_elem * 4)) {
                                int j = 0;
                                for( int i = 0; i < 6; i++) {
                                    if(tab[i] < max_elem) {
                                        j = i;
                                        break;
                                    }
                                }
                                int pom = tab[j++];
                                for(; j < 6; j++) {
                                    if(tab[j] < max_elem && tab[j] + pom == max_elem) {
                                        counter++;

                                        for( int i = 0; i < 6; i++)
                                            myFile << tab[i] << " ";

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
    return counter;
}

int Algorithm::AlgorithmMyHeuristic( std::ofstream &myFile) {
    quicksort(algorithmTable, 0, length-1);

    for( int i = 0; i < length; i++)
        myFile << "[" << i << "]: " << algorithmTable[i] << " \n";

    myFile << "===========================================\n";

	int sum = 0;
	int first = algorithmTable[0];
	int counter = 1;

	for	(int i = 1; i < length - 3; i++) { // bo może być warian ze 3 pierwsze liczby tej samej dlugosci
		if(algorithmTable[i] == first)
			counter++;

		else if(algorithmTable[i] != first && counter > 1) {
			sum += searchingTwoSidesOfSquare(i, counter, myFile);

			if(counter > 2)
				sum += searchingThreeSticks(i, counter, myFile);

			counter = 1;
			first = algorithmTable[i];
		}

		else // table[i]!=first && counter == 1
			first = algorithmTable[i];
	}
    return sum;
}

int partition(int tablica[], int p, int r) {
    int x = tablica[p];
    int i = p, j = r, w;
    while (true) {
        while (tablica[j] < x)
            j--;

        while (tablica[i] > x)
            i++;

        if (i < j) {
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

void Algorithm::quicksort(int tablica[], int p, int r) {
    int q;
    if (p < r) {
        q = partition(tablica,p,r);
        quicksort(tablica, p, q);
        quicksort(tablica, q+1, r);
    }
}

int newton(int n, int k) {
	int number = 1;
	for(int i = 1; i <= k; i++)
		number = number * ( n - i +1 ) / i;
	return number;
}

            //tmp - ile wariantow danego typu pojawilo sie
            //tmpi - ile takich samych liczb z gory pojawilo sie
            //tmpj - ile takich samych liczb z dolu pojawilo sie
//zwraca liczbe wariantow gdzie za pomoca 2 liczb mozna otrzymac sume algorithmTable[position-1]
int Algorithm::searchingTwoSidesOfSquare ( int position, int countedElements, std::ofstream &myFile) {
    int counter = 0;
    combination.clear(); // [n, a, b]
    int i = position, j = length - 1;
    int tmpi,tmpj,tmp;
    /*
    if(algorithmTable[i] == algorithmTable[j] && algorithmTable[i] * 2 == algorithmTable[position-1])
    {
        counter = newton(length - position, 4) * newton(countedElements, 2);
        std::cout << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " " << algorithmTable[i] << " " << algorithmTable[i] << " " << algorithmTable[i];
        std::cout << " the same 6 elements for " << counter << " combination."<<std::endl;
        return counter;
    }*/

    while( i != j && algorithmTable[i] >= (int)(algorithmTable[position-1] / 2) && algorithmTable[j] <= (int)(algorithmTable[position-1] / 2) ) {
        if(algorithmTable[i] + algorithmTable[j] > algorithmTable[position-1])
            i++;

        else if(algorithmTable[i] + algorithmTable[j] < algorithmTable[position-1])
            j--;

        else { //if(algorithmTable[i] + algorithmTable[j] == algorithmTable[position-1] )
            tmpi = 1;
            while(algorithmTable[i+1] + algorithmTable[j] == algorithmTable[position-1] ) {
                tmpi++;
                i++;
                if (i == position - 1)
                    break;
            }

            if( i != j) {
                tmpj = 1;
                while(algorithmTable[i] + algorithmTable[j-1] == algorithmTable[position-1]) {
                    tmpj++;
                    j--;
                }
                tmp = tmpj * tmpi;
            }

            else
                tmp = tmpi * (tmpi - 1) / 2;

            if(combination.empty()) {
                if(i == j)
                    counter = newton(countedElements, 2) * newton(tmpi, 4);
                else
                    counter = newton(countedElements, 2) * newton(tmpi, 2) * newton(tmpj, 2);

                if(counter > 0)
                    myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " " << algorithmTable[i] << " " << algorithmTable[j] << " " << algorithmTable[j] << " the same 6 elements for " << counter << " combination.\n";

                combination.push_back(tmp);
                combination.push_back(algorithmTable[i]);
                combination.push_back(algorithmTable[j]);
                i++;
            }

            else {
                int n, a, b;
                int counterTmp;
                for(unsigned int it = 0; it < combination.size();) { // wariant gdzie 1 i 2 liczba to max, 3 i 4 z wektora wzieta i 5 oraz 6 wyliczona w tej iteracji
                    n = combination[it++];
                    a = combination[it++];
                    b = combination[it++];

                    counterTmp = newton(countedElements, 2) * n * tmp ;
                    counter = counter + counterTmp;
                    myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << a << " " << b << " " << algorithmTable[i] << " " << algorithmTable[j] << " the same 6 elements for " << counterTmp << " combination.\n";
                }

                counterTmp = 0;
                if(i == j)
                    counterTmp = newton(countedElements, 2) * newton(tmpi, 4);

                else
                    counterTmp = newton(countedElements, 2) * newton(tmpi, 2) * newton(tmpj, 2);

                counter = counter + counterTmp;
                if(counterTmp > 0)
                    myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " " << algorithmTable[i] << " " << algorithmTable[j] << " " << algorithmTable[j] << " the same 6 elements for " << counterTmp << " combination.\n";

                combination.push_back(tmp);
                combination.push_back(algorithmTable[i]);
                combination.push_back(algorithmTable[j]);
                i++; // ewentualnie j-- mozna dodac i sprawdzic czy cos szybciej dziala
            }
        }
    }
    return counter;
}

int Algorithm::searchingThreeSticks (int position, int countedElements, std::ofstream &myFile) {
    int counter = 0;
    int tmpk, tmpj, tmpi;
    int counterTmp;

	for (int i = position; i < length - 2; i++) {
        int searchingSum = algorithmTable[position-1] - algorithmTable[i];

        tmpi = 1;
        while(algorithmTable[i] == algorithmTable[i+1]) {
            tmpi++;
            i++;
            if (i == position - 1)
                break;
        }

        int k = tmpi > 1 ? i : i + 1;

        for( int j = length - 1; algorithmTable[k] >= (int)(searchingSum / 2) && algorithmTable[j] <= (int)(searchingSum / 2); ) {
            if(algorithmTable[k] + algorithmTable[j] > searchingSum)
                k++;

            else if(algorithmTable[k] + algorithmTable[j] < searchingSum)
                j--;

            else {
                tmpk = 1;
                tmpj = 1;
                while(k != position - 1 && algorithmTable[k] == algorithmTable[k+1] ) {
                    tmpk++;
                    k++;
                }
                while(algorithmTable[j-1] == algorithmTable[j]) {
                    j--;
                    tmpj++;
                }


                if( algorithmTable[i] == algorithmTable[k]) {
                    if(algorithmTable[i] == algorithmTable[j] ) {
                        counterTmp = newton(countedElements, 3) * newton(tmpi, 3);
                        counter += counterTmp;
                        myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " " << algorithmTable[i] << " " << algorithmTable[i] << " the same 6 elements for " << counterTmp << " combination.\n";
                    }

                    else {
                        counterTmp = newton(countedElements, 3) * newton(tmpi, 2) * tmpj;
                        counter += counterTmp;
                        myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " " << algorithmTable[i] << " " << algorithmTable[j] << " the same 6 elements for " << counterTmp << " combination.\n";
                    }
                }

                else { //algorithmTable[i] != algorithmTable[k]
                    if(algorithmTable[k] == algorithmTable[j] && tmpk > 1) {
                        counterTmp = newton(countedElements, 3) * tmpi * newton(tmpk, 2);
                        counter += counterTmp;
                        myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " " << algorithmTable[k] << " " << algorithmTable[j] << " the same 6 elements for " << counterTmp << " combination.\n";
                    }
                    else if(algorithmTable[k] != algorithmTable[j]) {
                        counterTmp = newton(countedElements, 3) * tmpi * tmpj * tmpk;
                        counter += counterTmp;
                        myFile << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[position-1] << " " << algorithmTable[i] << " " << algorithmTable[k] << " " << algorithmTable[j] << " the same 6 elements for " << counterTmp << " combination.\n";
                    }
                }
            k++;
            }
        }
    }
    return counter;
}
#endif // ALGORITHM_H_INCLUDED
