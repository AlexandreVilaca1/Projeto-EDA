#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


Matrix *readMatrixFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Unable to open file.\n");
        return NULL;
    }

    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (matrix == NULL)
    {
        printf("Memory allocation failed.\n");
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

void insertRowEnd(Node *head, int value)
{
    Node *newNode = createNode(value);
    if (head == NULL)
    {
        printf("Invalid head node.\n");
        return;
    }

    Node *temp = head;
    while (temp->nextRow != NULL)
    {
        temp = temp->nextRow;
    }
    temp->nextRow = newNode;
}

void insertColEnd(Node *head, int value)
{
    Node *newNode = createNode(value);
    if (head == NULL)
    {
        printf("Invalid head node.\n");
        return;
    }

    Node *temp = head;
    while (temp->nextCol != NULL)
    {
        temp = temp->nextCol;
    }
    temp->nextCol = newNode;
}

void changeConstant(Matrix *matrix, int newValue)
{
    Node *tempRow = matrix->rowHead;
    while (tempRow != NULL)
    {
        Node *tempCol = tempRow;
        while (tempCol != NULL)
        {
            tempCol->value = newValue;
            tempCol = tempCol->nextCol;
        }
        tempRow = tempRow->nextRow;
    }
}

void insertNewRow(Matrix *matrix)
{
    Node *newRow = createNode(0);
    int value;

    if (matrix->rowHead == NULL)
    {
        matrix->rowHead = newRow;
    }
    else
    {
        Node *lastRow = matrix->rowHead;
        while (lastRow->nextRow != NULL)
        {
            lastRow = lastRow->nextRow;
        }
        lastRow->nextRow = newRow;
    }
    printf("Enter the value:");
    scanf("%d", &value);
    for (int i = 0; i < 5; i++)
    {
        insertColEnd(newRow, value);
    }
}

void insertNewColumn(Matrix *matrix)
{
    int value;
    Node *currentRow = matrix->rowHead;

    printf("Enter the value:");
    scanf("%d", &value);
    while (currentRow != NULL)
    {
        insertColEnd(currentRow, value);
        currentRow = currentRow->nextRow;
    }
}

void removeRow(Matrix *matrix, int rowIndex)
{
    if (matrix == NULL || matrix->rowHead == NULL)
    {
        printf("Matrix is empty.\n");
        return;
    }

    Node *currentRow = matrix->rowHead;
    Node *prevRow = NULL;
    int count = 0;

    // Traverse until the specified row index or the end of the matrix
    while (currentRow != NULL && count != rowIndex)
    {
        prevRow = currentRow;
        currentRow = currentRow->nextRow;
        count++;
    }

    if (currentRow == NULL)
    {
        printf("Invalid row index.\n");
        return;
    }

    // If the row to be deleted is the first row
    if (prevRow == NULL)
    {
        matrix->rowHead = currentRow->nextRow;
    }
    else
    {
        prevRow->nextRow = currentRow->nextRow;
    }

    // Free memory of nodes in the deleted row
    Node *temp = currentRow;
    while (temp != NULL)
    {
        Node *nextNode = temp->nextCol;
        free(temp);
        temp = nextNode;
    }
}

void removeColumn(Matrix *matrix, int colIndex)
{
    if (matrix == NULL || matrix->rowHead == NULL)
    {
        printf("Matrix is empty.\n");
        return;
    }

    Node *currentRow = matrix->rowHead;

    // Traverse each row
    while (currentRow != NULL)
    {
        Node *currentCol = currentRow;
        Node *prevCol = NULL;
        int count = 0;

        // Traverse until the specified column index or the end of the row
        while (currentCol != NULL && count != colIndex)
        {
            prevCol = currentCol;
            currentCol = currentCol->nextCol;
            count++;
        }

        if (currentCol == NULL)
        {
            printf("Invalid column index.\n");
            return;
        }

        // If the column to be deleted is the first column
        if (prevCol == NULL)
        {
            currentRow = currentCol->nextCol;
        }
        else
        {
            prevCol->nextCol = currentCol->nextCol;
        }

        free(currentCol); // Free memory of the deleted node

        currentRow = currentRow->nextRow; // Move to the next row
    }
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

    do
    {
        printf("\n===== Matrix Menu =====\n");
        printf("1. Display Matrix\n");
        printf("2. Update Matrix\n");
        printf("3. Insert New Row\n");
        printf("4. Insert New Column\n");
        printf("5. Remove Row from the Matrix\n");
        printf("6. Remove Column from the Matrix\n");
        printf("7. Display Tabular Listing\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nCurrent Matrix:\n");
            displayMatrix(matrix);
            break;
        case 2:
            printf("\nEnter the new constant to update the matrix: ");
            scanf("%d", &constant);
            changeConstant(matrix, constant);
            printf("Matrix updated successfully with constant %d.\n", constant);
            break;
        case 3:
            insertNewRow(matrix);
            printf("New row inserted into the matrix.\n");
            break;
        case 4:
            insertNewColumn(matrix);
            printf("New column inserted into the matrix.\n");
            break;
        case 5:
            printf("\nEnter the index of the row to remove: ");
            scanf("%d", &index);
            removeRow(matrix, index);
            break;
        case 6:
            printf("\nEnter the index of the column to remove: ");
            scanf("%d", &index);
            removeColumn(matrix, index);
            break;
        case 7:
            printf("\n===== Tabular Listing of Matrix Integers =====\n");
            displayTabularListing(matrix);
            break;
        case 8:
            printf("Exiting Matrix Menu. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
            break;
        }
    } while (choice != 8);
}