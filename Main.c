#include "Header.h"
#include <stdio.h>

int main() {
    // Assuming matrix is initialized and read from file
    Matrix* matrix = readMatrixFromFile("Numbers.txt");

    displayMatrixMenu(matrix);

    return 0;
}
    