#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* nextRow;
    struct Node* nextCol;
} Node;

typedef struct Matrix {
    Node* rowHead;
    Node* colHead;
} Matrix;

Node* createNode(int value);
void insertRowEnd(Node** head, int value);
void insertColEnd(Node** head, int value);
void displayMatrix(Matrix* matrix);
void changeConstant(Matrix* matrix, int newValue);
void displayMatrixMenu(Matrix* matrix);
void insertNewRow(Matrix* matrix);
void insertNewColumn(Matrix* matrix);
void displayTabularListing(Matrix* matrix);
Matrix* readMatrixFromFile(const char* filename);

