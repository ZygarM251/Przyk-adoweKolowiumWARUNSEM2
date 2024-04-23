#pragma once
#include <iostream>
#include <iomanip>
#pragma warning(disable:4996)

int** alokuj(int wiersze, int kolumny);
void zapisz(int** tab, int wiersze, int kolumny, const char* nazwa);
int** odczytaj(int& wiersze, int& kolumny, const char* nazwa);
void dealokuj(int** tab);