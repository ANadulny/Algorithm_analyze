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
