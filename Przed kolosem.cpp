#include <iostream>
#include <fstream>  // Dla ofstream
#include <cstdio>  // Dla FILE*, fopen, fwrite, fclose
#include <cstdint>
#pragma warning(disable:4996)

using namespace std;

int globalny_id = 0;

// Funkcja do alokacji tablicy
short* alokujTablice(int rozmiar) {
    short* tablica = new short[rozmiar];
    for (int i = 0; i < rozmiar; ++i) {
        tablica[i] = 0;  // Inicjalizujemy zerami
    }
    return tablica;
}

// Funkcja do zapisu tablicy do pliku binarnego z ID
void zapiszTabliceDoPliku(const std::string& nazwa_pliku, short* tablica, int rozmiar) {
    FILE* plik = fopen(nazwa_pliku.c_str(), "wb");  // Otwarcie pliku w trybie binarnym
    if (!plik) {
        std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
        return;
    }

    // Zapisujemy rozmiar tablicy
    fwrite(&rozmiar, sizeof(int), 1, plik);

    // Zapisujemy dane tablicy
    fwrite(tablica, sizeof(short), rozmiar, plik);

    fclose(plik);  // Zamykamy plik po zapisie
}

// Funkcja do odczytu tablicy z pliku binarnego
short* odczytajTabliceZPliku(const std::string& nazwa_pliku, int& rozmiar) {
    FILE* plik = fopen(nazwa_pliku.c_str(), "rb");  // Otwarcie pliku w trybie binarnym
    if (!plik) {
        std::cerr << "Nie można otworzyć pliku do odczytu." << std::endl;
        return nullptr;
    }

    // Odczytujemy rozmiar tablicy
    fread(&rozmiar, sizeof(int), 1, plik);

    // Alokujemy nową tablicę
    short* tablica = new short[rozmiar];

    // Odczytujemy dane tablicy
    fread(tablica, sizeof(short), rozmiar, plik);

    fclose(plik);  // Zamykamy plik po odczycie

    return tablica;
}

void zwolnijTablice(short* tablica) {
    if (tablica != nullptr) {
        delete[] tablica;  
        tablica = nullptr;  
    }
}

int main()
{
    int ilosc_tablic = 3;  
    int rozmiar_tablicy = 10;  

    for (int i = 0; i < ilosc_tablic; ++i) {
        short* tablica = alokujTablice(rozmiar_tablicy);
        for (int j = 0; j < rozmiar_tablicy; ++j) {
            tablica[j] = j + i * 10; 
        }

        const char* nazwa_pliku = "Tekst.txt";
        zapiszTabliceDoPliku(nazwa_pliku, tablica, rozmiar_tablicy);

        delete[] tablica;
    }

    // Pobieramy od użytkownika numer tablicy do odczytu
    int numer_tablicy;
    cout << "Podaj numer tablicy do odczytu od 0 do 2: ";
    cin >> numer_tablicy;

    const char* nazwa_pliku = "Tekst.txt";

    int odczytany_rozmiar = 0;
    short* odczytana_tablica = odczytajTabliceZPliku(nazwa_pliku, odczytany_rozmiar);

    if (odczytana_tablica) {
        cout << "Odczytano tablicę o rozmiarze: " << odczytany_rozmiar << endl;

        for (int i = 0; i < odczytany_rozmiar; ++i) {
            cout << "Element " << i << ": " << odczytana_tablica[i] << endl;
        }
        delete[] odczytana_tablica;
    }
    else {
        cerr << "Nie udało się odczytać tablicy." << endl;
    }

    zwolnijTablice(odczytana_tablica);
}

