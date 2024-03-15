#include "Header.h"
#include <stdio.h>

int main() {
    Matrix* matrix = readMatrixFromFile("Numbers.txt");

    displayMatrixMenu(matrix);

    return 0;
}
    