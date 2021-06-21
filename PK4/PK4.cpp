#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
std::vector <int> piramida(std::vector <int> dane, int dlugoscPodstawy, int& naj) {
    int dlugoscDanych = dane.size();
    int i = 0;
    while (dlugoscPodstawy > 1) {
        i = 1;
        // tworzenie kolejnych poziomow piramidy
        while (i < dlugoscPodstawy) {
            dane.push_back(dane[dlugoscDanych - dlugoscPodstawy] + dane[dlugoscDanych - dlugoscPodstawy + 1]); // dodawania na koniec vectora sum kolejnych par
            dlugoscDanych++;
            i++;
        }
        dlugoscPodstawy--;
    }
    return dane;
}

void wypisz(std::vector<int> wynik, int n) {
    int a = 0;
    int b = n;
    int c = 0;
    for (a; a < wynik.size(); a++) {
        std::cout << wynik[a] << "  |  ";
        b--;
        if (b == 0) {
            c++;
            b = n - c;
            std::cout << "\n";
        }
    }
    std::cout << "\nNajmniejsza mozliwa liczba u szczytu piramidy to: " << wynik.back() << "\n";

    std::ofstream file("wynik.txt");
    file << wynik.back();
    file.close();

    return;
}

void kombinacje(int dlugoscPodstawy) {
    int i = 0;
    int dlugosc = std::pow(2, (dlugoscPodstawy / 2) + 1); // limit gorny
    int najwieksza = INT_MAX;
    std::vector <int> dane;
    std::vector <int> znaleziona;

    while (i < dlugoscPodstawy) {
        dane.push_back(1);
        i++;
    }

    while (dane[dlugoscPodstawy - 1] <= dlugosc) { // dopoki ostatni element podstawy jest mniejszy niz limit gorny
        i = 0;
        dane[0]++;
        while (i < dlugoscPodstawy - 1) { // iteracja przez podstawe
            if (dane[i] > dlugosc) { // szukamy takiego elementu w tablicy ktory jest wiekszy niz dlugosc
                dane[i + 1]++;
                dane[i] = 1;
            }
            i++;
        }
        std::vector <int> wynik = piramida(dane, dlugoscPodstawy, najwieksza);
        std::vector<int> kopia = wynik;
        sort(kopia.begin(), kopia.end());
        std::vector<int>::iterator it = std::unique(kopia.begin(), kopia.end());
        bool czyBylyDuplikaty = (it == kopia.end());

        if (czyBylyDuplikaty && (wynik.back() < najwieksza)) {
            najwieksza = wynik.back();
            znaleziona = wynik;
        }
    }
    wypisz(znaleziona, dlugoscPodstawy);

    return;
}




int main()
{
    int dlugoscPodstawy;
    std::cout << "Podaj liczbe liczb w pierwszym rzedzie piramidy\n";
    std::cin >> dlugoscPodstawy;
    std::cout << "\n";
    kombinacje(dlugoscPodstawy); //do 6 dziala fajnie, 7 pare minut moze zajac ale pojawi sie, 8+ to chyba nie ma tyle czasu
    return 0;
}

