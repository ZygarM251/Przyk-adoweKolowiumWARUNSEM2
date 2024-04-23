#include "Nag³ówek.h"
#pragma warning(disable:4996)

int** alokuj(int wiersze, int kolumny) {
    int** tab = new int* [wiersze + 1];

    for (int i = 0; i <= wiersze; ++i) {
        tab[i] = new int[kolumny];
    }

    int rozmiar = (wiersze << 16) | kolumny;
    tab[0][0] = rozmiar;

    return tab + 1;
}

void zwolnij(int** tab, int liczbaWierszy) {

    int** tablica = tab - 1;

    for (int i = 0; i <= liczbaWierszy; ++i) {
        delete[] tablica[i];
    }

    delete[] tablica;
}

void zapiszTablice(int** tab, int wiersze, int kolumny, const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "wb");  

    if (plik == nullptr) {
        cerr << "Nie mo¿na otworzyæ pliku" << endl;
        return;
    }

    int rozmiar = tab[-1][0];  
    fwrite(&rozmiar, sizeof(int), 1, plik);

    for (int i = 0; i < wiersze; ++i) {
        fwrite(tab[i], sizeof(int), kolumny, plik);
    }

    fclose(plik); 
}


int** odczytajTablice(const char* nazwaPliku, int& wiersze, int& kolumny) {
    FILE* plik = fopen(nazwaPliku, "rb"); 

    if (plik == nullptr) {
        cerr << "Nie mo¿na otworzyæ pliku do odczytu." << endl;
        return nullptr;
    }
    int rozmiar;
    fread(&rozmiar, sizeof(int), 1, plik);

    wiersze = (rozmiar >> 16);  // Najstarsze bajty to liczba wierszy
    wiersze = (rozmiar & 0xFFFF);  // Najm³odsze bajty to liczba kolumn

    int** tab = new int* [wiersze];
    for (int i = 0; i < wiersze; ++i) {
        tab[i] = new int[kolumny];
    }

    for (int i = 0; i < wiersze; ++i) {
        fread(tab[i], sizeof(int), kolumny, plik);
    }

    fclose(plik);  
    return tab;  
}
