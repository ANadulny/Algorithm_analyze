# AAL
Treść zadania 9:
Mamy zestaw S niełamalnych patyków o długości si, gdzie i∈(1,2,...,S). Zaproponuj algorytm wyliczający na ile sposobów można zbudować kwadrat przy użyciu 6 z tych patyków i wyznaczyć, których patyków należy użyć.

## Koncepcja rozwiązania zadania

Zadanie rozwiążę korzystając z języka C++. 

Na początku wygeneruję losowo listę S elementową przy wykorzystaniu biblioteki random.

Następnie zaprezentuję algorytm naiwny, który będzie polegał na sprawdzeniu każdego możliwego wariantu wyboru 6 liczb z listy S elementowej. Dokonam tego przy użyciu 6 pętli (każda pętla wyznacza jedną z sześciu liczb) w których będę rozważał 2 możliwe warianty zbudowania kwadratu przy pomocy 6 liczby. 

Wariant I: Trzy największe liczby z 6 wybranych są tej samej długości, wtedy z 3 pozostałych liczb budujemy ostatni bok kwadratu. Zatem będziemy dodawać do siebie 3 najmniejsze liczby z wybranych 6 liczb i sprawdzać czy ich suma jest równa największej liczbie mini zbioru.
Jeżeli tak jest to znaczy, że znaleziono zestaw liczb za pomocą których można zbudować kwadrat.

Wariant II: Dwie największe liczby z 6 wybranych są tej samej długości, wtedy z 4 pozostałych liczb budujemy 2 boki kwadratu. Będzie to wyglądało tak, że 2 boki kwadratu będą składały się z dwóch największych liczb, a pozostałe 2 boki powinny być sumą dwóch liczb równą największej liczbie mini zbioru.
Jeżeli tak jest to znaczy, że znaleziono zestaw liczb za pomocą których można zbudować kwadrat.

- Mini zbiór – to zbiór złożony z 6 liczb wybranych za pomocą pętli.

Swoja heurystyka:

Na początku listę S elementową posortuję malejąco. Następnie zaczynając od pierwszego największego elementu listy i będę szukać co najmniej pary liczb powtarzającej się. Dla kolejnych znalezionych takich par będę rozważał wariant II i wariant I (jeżeli co najmniej 3 kolejne liczby powtórzą się) z algorytmu naiwnego z małą modyfikacją dotyczącą wyboru odpowiednio 4 lub 3 pozostałych liczb. Koniecznie będzie zliczenie ile liczb powtarza się.

Wybór 4 pozostałych liczb: Wyszukiwanie wszystkich możliwych wariantów zsumowania dwóch liczb tak, żeby dana suma była równa liczbie dla której stosujemy wariant I lub II. Wyznaczenie takich par liczb, z dwóch różnych miejsc listy, odbywać będzie się poprzez sprawdzanie sumy liczb odpowiednio wybierając od końca listy S elementowej większe liczby i liczby następne w liście różne od liczby dla której szukamy 4 mniejszych liczb. Spełniające założenie kombinacje par liczb zliczamy i na ich podstawie korzystając z symbolu newtona będzie można wyznaczyć liczbę kwadratów spełniający obecny wariant.

Wybór 3 pozostałych liczb: Wstępnie w zbiorze 6 elementów mamy już 3 powtarzające się liczby. Czwartym elementem tego zbioru będzie liczba następna w liście różne od liczby dla które wyznaczamy dany wariant. Wtedy potrzebujemy już tylko 2 elementów zbioru z którego można zbudować kwadrat. Takie 2 liczby będzie można wybrać korzystając z części wariantu wcześniejszego dla szukania pary liczb dających tym razem sumę pomniejszonej największej liczby zbioru 6 elementowego o czwarty element, który do tego zbioru dodaliśmy. 

Testy algorytmu zamierzam wykonać za pomocą biblioteki boost/test/unit_test.hpp.

Pomiarów czasów działania algorytmów zamierzam dokonać przy pomocy biblioteki chrono.

Projekt będzie budowany przy pomocy programu make. Podczas kompilowania programu od razu będą sprawdzane testy jednostkowe z biblioteki boost/test/unit_test.hpp.

## Metody do zaimplementowania w projekcie:

### W pliku Algorithm.cpp:

- int AlgorithmNaive(int table[], int length)		[n^7]
Metoda odpowiedzialna za poprawne działanie algorytmu naiwnego na podstawie powyższej koncepcji.

- int AlgorithmMyHeuristic (int table[], int length)		[n^3 + n^2 + n + n*logn]
Metoda odpowiedzialna za poprawne działanie algorytmu heurystyki, którą opisałem we wcześniejszym punkcie dokumentacji. Dana metoda będzie wywoływała na początku swojego działania jedną z metod sortowania tablicy. Przetestuję za pomocą testów jednostkowych, który algorytm sortowania szybciej będzie działał dla wejściowych tablic o dużej liczbie powtarzalnych elementów i wybiorę najszybciej działający algorytm,  żeby czas wykonywania metody AlgorithmMyHeuristic był jak najkrótszy.  Skorzystam tutaj z następujących metod do przetestowania:

- void quicksort(int tablica[], int p, int r)	[ n * log2 n]
Dla algorytmu sortowania quicksort. 
http://www.algorytm.org/algorytmy-sortowania/sortowanie-szybkie-quicksort/quick-1-c.html

- void merge(int tab[], int start, int srodek, int end)
- void merge_sort(int tab[], int start, int end)  		[n * log2 n]
Dla algorytmu mergesort.
http://www.algorytm.org/algorytmy-sortowania/sortowanie-przez-scalanie-mergesort/merge-1-c.html

- void bubblesort(int *tab, int rozmiar)		[n^2]
Dla algorytmu sortowania bąbelkowego.
http://www.algorytm.org/algorytmy-sortowania/sortowanie-babelkowe-bubblesort/bubble-1-c.html

- int searchingTwoSidesOfSquare (int tab[], int length, int position, int searchingSum)	[n+1]
Metoda odpowiedzialna za zliczanie par liczb sumujących się do wartości searchingSum. Sprawdzanie sum kolejnych par liczb zaczynamy równolegle z pozycji position + 1 i length – 1, gdzie position + 1 będziemy przy odpowiednim warunku zwiększali o 1, a length – 1 zmniejszali o 1, oczywiście dalej sumując liczby aż do momentu, gdy te dwie liczby dotyczące pozycji elementów w tablicy będą sobie równe. Metoda zwraca liczbę par spełniających wyżej wymienione założenie.

- int searchingThreeSticks (int tab[], int length, int position)	[n^2]
Metoda będzie odpowiedzialna za zliczanie kombinacji przy użyciu takich 3 liczb z tablicy, których suma równa będzie tab[position]. Parametr position określa pozycję ostatniego powtarzającego się elementu w tablicy. Kolejne liczby z tablicy znajdujące się na pozycjach większych od position będą wybierane i dla nich będzie obliczana różnica:            tab[position] - tab[position+i] , gdzie i = 1 oraz i < length-2; Dopiero teraz będzie można posłużyć się metodą searchingTwoSidesOfSquare dla której nowy parametr position będzie równy position+i, a searchingSum równa będzie obliczonej trochę wyżej różnicy.

- void algorithmTimeMeasure (int& algorithm(int table[], int length))     
Metoda wyliczająca czas trwania algorytmu.

### W pliku Sticks.h:
- void generateStickTable()
Metoda generująca liczby od 1 do S (S oznaczone w klasie będzie jako int stickNumber) i wstawiająca je do kolejnych miejsc w tablicy.

