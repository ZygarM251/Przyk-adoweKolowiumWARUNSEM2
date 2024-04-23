#pragma once

#include <iostream>
#include <cstdio>  
#include <cstdlib> 

using namespace std;

int** alokuj(int wiersze, int kolumny);

void zwolnij(int** tab, int liczbaWierszy);

void zapiszTablice(int** tab, int wiersze, int kolumny, const char* nazwaPliku);

int** odczytajTablice(const char* nazwaPliku, int& wiersze, int& kolumny);