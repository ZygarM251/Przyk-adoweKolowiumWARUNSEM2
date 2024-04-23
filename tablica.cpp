#include <iostream>
#include <iomanip>
#include "tablica.h"
#pragma warning(disable:4996)

using namespace std;

int** alokuj(int wiersze, int kolumny)
{
	int** tab = new int* [wiersze + 1];
	for (int i = 0; i < wiersze + 1; i++)
	{
		tab[i] = new int[kolumny+1];
	}
	tab[-1] = new int[2];
	tab[-1][0] = (wiersze << 16) | kolumny;
	tab[-1][1] = kolumny;
	return tab + 1;
}


void zapisz(int** tab, int wiersze, int kolumny, const char* nazwa)
{
	FILE* plik = fopen(nazwa, "w+b");
	if (!plik) 
	{
		cerr << "Nie mo¿na otworzyæ pliku do zapisu." << endl;
		return;
	}

	fwrite(&(tab[-1][0]), sizeof(int), 1, plik);
	fwrite(&(tab[-1][1]), sizeof(int), 1, plik);
	for (int i = 0; i < wiersze; i++)
	{
		fwrite(tab[i], sizeof(int), kolumny, plik);
	}

	fclose(plik);
	dealokuj(tab - 1);
}

int** odczytaj(int& wiersze, int& kolumny, const char* nazwa)
{
	FILE* plik = fopen(nazwa, "r+b");
	if (!plik) {
		cerr << "Nie mo¿na otworzyæ pliku do odczytu." << endl;
		return nullptr;
	}

	fread(&wiersze, sizeof(int), 1, plik);
	fread(&kolumny, sizeof(int), 1, plik);
	int** tab = alokuj(wiersze, kolumny);
	for (int i = 0; i < wiersze; i++)
	{
		fread(tab[i], sizeof(int), kolumny, plik);
	}

	fclose(plik);
	return tab;
} 

void dealokuj(int** tab)
{
	delete[] (tab - 1);
}