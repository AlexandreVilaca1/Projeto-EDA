#include <stdbool.h>
/**
 * @file Header.h 
 * @brief Este arquivo é uma livraria que contém as declarações  das funções e structs utilizadas no sistema de forma a facilitar a reutilização do código.
 */

/**
 * @brief Struct que representa um node de uma matriz.
 * 
 * Esta struct representa um node de uma matriz, contendo um valor inteiro,
 * bem como informações sobre a posição do node na matriz (linha e coluna).
 * Além disso, possui ponteiros para o próximo node na mesma linha (nextRow)
 * e na mesma coluna (nextCol).
 */
typedef struct Node
{
    int value;
    int row;
    int col;
    struct Node *nextRow;
    struct Node *nextCol;
} Node;

/**
 * @brief Struct que representa uma matriz.
 * 
 * Esta struct representa uma matriz, que é composta por pointers que apontam para o início de uma linha e coluna na matriz.
 */
typedef struct Matrix
{
    Node *rowHead;
    Node *colHead;
} Matrix;

/**
 * Function: readMatrixFromFile
 * ------------------------------------------
 * Esta função recebe um nome de ficheiro como entrada, abre o ficheiro em modo de leitura e lê o conteúdo do ficheiro e cria nodes conforme os valores do ficheiro.
 * A matriz é representada como uma lista ligada de nós, onde cada nó contém um valor e ponteiros para o próximo node na linha e coluna.
 */
Matrix *readMatrixFromFile(const char *filename);

/**
 * Function: createNode
 * ------------------------------------------
 * A função createNode cria um novo node para a matriz e aloca memória para o node, inicializa o seu valor com o input fornecido e define os pointers para a 
 * próxima linha e coluna com o valor NULL para defenir como fim da lista.
 */
Node *createNode(int value);

/**
 * Function: displayMatrix
 * ------------------------------------------
 * A função displayMatrix mostra a matriz armazenada na memória, onde percorre cada linha e coluna da matriz a partir de pointers e imprime os seus valores.
 */
void displayMatrix(Matrix *matrix);

/**
 * Function: insertRowEnd
 * ------------------------------------------
 * A seguinte função insere um novo node no final de uma linha na matriz.
 * Se a linha estiver vazia, define o início com o novo node, caso contrário, percorre a linha até encontrar o último node e insere-o lá.
 */
Node *insertRowEnd(Node *head, int value);

/**
 * Function: insertColEnd
 * ------------------------------------------
 * A seguinte função insere um novo node no final de uma coluna na matriz.
 * Se a coluna estiver vazia, define o início com o novo node, caso contrário, percorre a coluna até encontrar o último node e insere-o lá.
 */
Node *insertColEnd(Node *head, int value);

/**
 * Function: changeConstant
 * ------------------------------------------
 * Esta função atualiza todos os valores na matriz com um novo valor.
 * Percorre cada node e atualiza o seu valor para a nova constante.
 */
Matrix *changeConstant(Matrix *matrix, int rowIndex, int colIndex, int newValue);
/**
 * Function: insertNewRow
 * ------------------------------------------
 * A função insertNewRow insere uma nova linha no final da matriz, cria uma nova linha com valores inseridos pelo utilizador e coloca-os no final da matriz.
 */
Matrix *insertNewRow(Matrix *matrix);

/**
 * A função insertNewColumn insere uma nova coluna no final da matriz, cria uma nova coluna com valores inseridos pelo utilizador e coloca-os no final da matriz.
 */
Matrix *insertNewColumn(Matrix *matrix);

/**
 * Function: removeRow
 * ------------------------------------------
 * A seguinte função remove uma linha específica, referida pelo utilizador, de uma matriz.
 */
Matrix *removeRow(Matrix *matrix, int rowIndex);

/**
 * Function: removeColumn
 * ------------------------------------------
 * A seguinte função remove uma coluna específica, referida pelo utilizador, de uma matriz.
 */
Matrix *removeColumn(Matrix *matrix, int colIndex);

/**
 * Function: displayTabularListing
 * ------------------------------------------
 * Esta função mostra a matriz num formato tabular.
 * É parecida com a displayMatrix(), percorre cada linha e coluna da matriz e imprime os valores só que no formato tabular.
 */
void displayTabuladrListing(Matrix *matrix);

/**
 * Function: displayTabularListing
 * ------------------------------------------
 * A seguinte função mostra um menu para o utilizador poder interagir com a matriz.
 */
void displayMatrixMenu(Matrix *matrix);





