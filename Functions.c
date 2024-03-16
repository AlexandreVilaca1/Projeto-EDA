#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
/**
 * @file functions.c
 * @brief Este arquivo contém a implementação das funções do sistema.
 * Essas funções abrangem a leitura de ficheiros, a criação de nodes, inserir e remover linhas e colunas na matriz, alteração de valores na matriz.
 */

Matrix *readMatrixFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (matrix == NULL)
    {
        fclose(file);
        return NULL;
    }
    matrix->rowHead = NULL;
    matrix->colHead = NULL;

    int count = 0;
    int value;
    Node *row = NULL;
    Node *prevRow = NULL;
    char ch;

    while (fscanf(file, "%d", &value) != EOF && (fscanf(file, "%c", &ch) != EOF))
    {
        if (count % 5 == 0)
        {
            row = createNode(value);
            if (matrix->rowHead == NULL)
            {
                matrix->rowHead = row;
            }
            else
            {
                prevRow->nextRow = row;
            }
            prevRow = row;
        }
        else
        {
            insertColEnd(row, value);
        }

        count++;
    }

    fclose(file);
    return matrix;
}

Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->value = value;
        newNode->nextRow = NULL;
        newNode->nextCol = NULL;
    }
    return newNode;
}

void displayMatrix(Matrix *matrix)
{
    Node *tempRow = matrix->rowHead;
    while (tempRow != NULL)
    {
        Node *tempCol = tempRow;
        while (tempCol != NULL)
        {
            printf("%d ", tempCol->value);
            tempCol = tempCol->nextCol;
        }
        printf("\n");
        tempRow = tempRow->nextRow;
    }
}

Node *insertRowEnd(Node *head, int value)
{
    Node *newNode = createNode(value);
    if (head == NULL)
    {
        return NULL;
    }

    Node *temp = head;
    while (temp->nextRow != NULL)
    {
        temp = temp->nextRow;
    }
    temp->nextRow = newNode;
    return newNode;
}

Node *insertColEnd(Node *head, int value)
{
    Node *newNode = createNode(value);
    if (head == NULL)
    {
        return NULL;
    }

    Node *temp = head;
    while (temp->nextCol != NULL)
    {
        temp = temp->nextCol;
    }
    temp->nextCol = newNode;
    return newNode;
}

Matrix *changeConstant(Matrix *matrix, int rowIndex, int colIndex, int newValue)
{
    Node *tempRow = matrix->rowHead;
    int currentRow = 0;

    while (tempRow != NULL && currentRow < rowIndex)
    {
        tempRow = tempRow->nextRow;
        currentRow++;
    }

    if (tempRow == NULL || currentRow != rowIndex)
    {
        return matrix;
    }

    Node *tempCol = tempRow;
    int currentCol = 0;

    while (tempCol != NULL && currentCol < colIndex)
    {
        tempCol = tempCol->nextCol;
        currentCol++;
    }

    if (tempCol == NULL || currentCol != colIndex)
    {
        return matrix;
    }

    tempCol->value = newValue;

    printf("Value at position (%d, %d) changed sucessfully to %d.\n", rowIndex, colIndex, newValue);

    return matrix;
}

Matrix *insertNewRow(Matrix *matrix)
{
    int value;

    Node *newRow = NULL;
    Node *lastRow = matrix->rowHead;

    if (lastRow == NULL)
    {
        matrix->rowHead = createNode(0);
        lastRow = matrix->rowHead;
    }
    else
    {

        while (lastRow->nextRow != NULL)
        {
            lastRow = lastRow->nextRow;
        }
        lastRow->nextRow = createNode(0);
        lastRow = lastRow->nextRow;
    }


    Node *currentRow = matrix->rowHead;
    while (currentRow != NULL)
    {
        printf("Enter value: ");
        scanf("%d", &value);
        insertColEnd(lastRow, value);

        currentRow = currentRow->nextRow;
    }

    return matrix;
}

Matrix *insertNewColumn(Matrix *matrix)
{
    int value;
    Node *currentRow = matrix->rowHead;


    while (currentRow != NULL)
    {
        printf("Enter the value: ");
        scanf("%d", &value);
        insertColEnd(currentRow, value);
        currentRow = currentRow->nextRow;
    }
    return matrix;
}

Matrix *removeRow(Matrix *matrix, int rowIndex)
{
    if (matrix == NULL || matrix->rowHead == NULL)
    {
        return matrix;
    }

    Node *currentRow = matrix->rowHead;
    Node *prevRow = NULL;
    int count = 0;

    while (currentRow != NULL && count != rowIndex)
    {
        prevRow = currentRow;
        currentRow = currentRow->nextRow;
        count++;
    }

    if (currentRow == NULL)
    {
        return matrix;
    }

    if (prevRow == NULL)
    {
        matrix->rowHead = currentRow->nextRow;
    }
    else
    {
        prevRow->nextRow = currentRow->nextRow;
    }

    Node *temp = currentRow;
    while (temp != NULL)
    {
        Node *nextNode = temp->nextCol;
        free(temp);
        temp = nextNode;
    }
    return matrix;
}

Matrix *removeColumn(Matrix *matrix, int colIndex)
{
    if (matrix == NULL || matrix->rowHead == NULL)
    {
        return matrix;
    }

    Node *currentRow = matrix->rowHead;

    while (currentRow != NULL)
    {
        Node *currentCol = currentRow;
        Node *prevCol = NULL;
        int count = 0;

        while (currentCol != NULL && count != colIndex)
        {
            prevCol = currentCol;
            currentCol = currentCol->nextCol;
            count++;
        }

        if (currentCol == NULL)
        {
            return matrix;
        }

        if (prevCol == NULL)
        {
            currentRow = currentCol->nextCol;
        }
        else
        {
            prevCol->nextCol = currentCol->nextCol;
        }

        free(currentCol);

        currentRow = currentRow->nextRow;
    }
    return matrix;
}

void displayTabularListing(Matrix *matrix)
{
    Node *currentRow = matrix->rowHead;

    while (currentRow != NULL)
    {
        Node *currentCol = currentRow;

        while (currentCol != NULL)
        {
            printf("%d\t", currentCol->value);
            currentCol = currentCol->nextCol;
        }

        printf("\n");
        currentRow = currentRow->nextRow;
    }
}

void displayMatrixMenu(Matrix *matrix)
{
    int choice;
    int constant;
    int index;
    int rowIndex, colIndex, newValue;

    do
    {
        printf("\n===== Matrix Menu =====\n");
        printf("[1] Display Matrix\n");
        printf("[2] Update Matrix\n");
        printf("[3] Insert New Row\n");
        printf("[4] Insert New Column\n");
        printf("[5] Remove Row from the Matrix\n");
        printf("[6] Remove Column from the Matrix\n");
        printf("[7] Display Tabular Listing\n");
        printf("[8] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nCurrent Matrix:\n");
            displayMatrix(matrix);
            break;
        case 2:
            printf("\nEnter the row index: ");
            scanf("%d", &rowIndex);
            printf("Enter the column index: ");
            scanf("%d", &colIndex);
            printf("Enter the new value: ");
            scanf("%d", &newValue);
            matrix = changeConstant(matrix, rowIndex, colIndex, newValue);
            break;
            break;
        case 3:
            printf("Enter the values for the new row:\n");
            matrix = insertNewRow(matrix);
            printf("New row inserted into the matrix.\n");
            break;
        case 4:
        printf("Enter the values for the new column:\n");
            matrix = insertNewColumn(matrix);
            printf("New column inserted into the matrix.\n");
            break;
        case 5:
            printf("\nEnter the index of the row to remove: ");
            scanf("%d", &index);
            matrix = removeRow(matrix, index);
            break;
        case 6:
            printf("\nEnter the index of the column to remove: ");
            scanf("%d", &index);
            matrix = removeColumn(matrix, index);
            break;
        case 7:
            printf("\n===== Tabular Listing of Matrix Integers =====\n");
            displayTabularListing(matrix);
            break;
        case 8:
            printf("Exiting Matrix Menu...\n");
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
            break;
        }
    } while (choice != 8);
}