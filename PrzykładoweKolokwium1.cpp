#include "Nagłówek.h"

int main()
{
    int rows = 3;
    int cols = 5;
    int** myArray = alokuj(rows, cols);

    // Wypełnienie tablicy przykładowymi danymi
    int value = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            myArray[i][j] = value++;
        }
    }

    // Zapis tablicy do pliku binarnego
    zapiszTablice(myArray, rows, cols, "Tekst.txt");

    // Zwalnianie pamięci
    zwolnij(myArray, rows);

    return 0;
  
}

