#include <iostream>
#include <iomanip>
#include "tablica.h"
#pragma warning(disable:4996)

using namespace std;



int main()
{
    int wiersze = 3;
    int kolumny = 4;

    int** mojaTablica = alokuj(wiersze, kolumny);

    // Wype�nienie tablicy przyk�adowymi danymi
    for (int i = 0; i < wiersze; ++i) {
        for (int j = 0; j < kolumny; ++j) {
            mojaTablica[i][j] = i * kolumny + j; 
        }
    }

    // Zapis tablicy do pliku
    zapisz(mojaTablica, wiersze, kolumny, "tablicabin.txt");

    // Dealokacja pami�ci
    dealokuj(mojaTablica);

    // Odczyt tablicy z pliku
    int** odczytanaTablica = nullptr;
    int odczytaneWiersze, odczytaneKolumny;
    odczytanaTablica = odczytaj(odczytaneWiersze, odczytaneKolumny, "tablicabin.txt");

    // Wy�wietlenie odczytanej tablicy
    if (odczytanaTablica != nullptr) {
        for (int i = 0; i < odczytaneWiersze; ++i) {
            for (int j = 0; j < odczytaneKolumny; ++j) {
                cout << odczytanaTablica[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Dealokacja pami�ci
    dealokuj(odczytanaTablica);
}