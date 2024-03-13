#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

// Function to create a new node
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

// Function to insert a node at the end of a row
void insertRowEnd(Node **head, int value)
{
    Node *newNode = createNode(value);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while (temp->nextRow != NULL)
        {
            temp = temp->nextRow;
        }
        temp->nextRow = newNode;
    }
}

// Function to insert a node at the end of a column
void insertColEnd(Node **head, int value)
{
    Node *newNode = createNode(value);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while (temp->nextCol != NULL)
        {
            temp = temp->nextCol;
        }
        temp->nextCol = newNode;
    }
}

// Function to display the matrix
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
        tempRow = tempRow->nextRow; // Avança para a próxima linha
    }
}
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
            insertColEnd(&row, value);
        }

        count++;
    }

    fclose(file);
    return matrix;
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

    for (int i = 0; i < 5; i++)
    {
        insertColEnd(&newRow, 0); // Initialize row elements with default value
    }
}

void insertNewColumn(Matrix *matrix)
{
    Node *currentRow = matrix->rowHead;

    while (currentRow != NULL)
    {
        insertColEnd(&currentRow, 0); // Initialize new column elements with default value
        currentRow = currentRow->nextRow;
    }
}

void displayTabularListing(Matrix* matrix) {
    Node* currentRow = matrix->rowHead;

    printf("\n===== Tabular Listing of Matrix Integers =====\n");

    while (currentRow != NULL) {
        Node* currentCol = currentRow;
        
        while (currentCol != NULL) {
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

    do
    {
        printf("\n===== Matrix Menu =====\n");
        printf("1. Display Matrix\n");
        printf("2. Update Matrix\n");
        printf("3. Insert New Row\n");
        printf("4. Insert New Column\n");
        printf("5. Display Tabular Listing\n");
        printf("6. Exit\n");
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
            printf("\n===== Tabular Listing of Matrix Integers =====\n");
            displayTabularListing(matrix);
            break;
        case 6:
            printf("Exiting Matrix Menu. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
            break;
        }
    } while (choice != 6);
}
