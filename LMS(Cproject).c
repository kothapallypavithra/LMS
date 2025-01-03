#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE 100
#define FILENAME "library.dat"

// Struct Definition
typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_TITLE];
    int year;
    int pages;
} Book;

// Function Prototypes
void addBook(Book books[], int *numBooks);
void printBooks(Book books[], int numBooks);
void saveToFile(Book books[], int numBooks);
void loadFromFile(Book books[], int *numBooks);

// Add Book
void addBook(Book books[], int *numBooks) {
    Book newBook;

    printf("\nEnter book title: ");
    fgets(newBook.title, MAX_TITLE, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter book author: ");
    fgets(newBook.author, MAX_TITLE, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter publication year: ");
    if (scanf("%d", &newBook.year) != 1) {
        printf("Invalid input. Year must be a number.\n");
        return;
    }

    printf("Enter number of pages: ");
    if (scanf("%d", &newBook.pages) != 1) {
        printf("Invalid input. Pages must be a number.\n");
        return;
    }

    getchar(); // Clear newline character

    newBook.id = (*numBooks) + 1;
    books[*numBooks] = newBook;
    (*numBooks)++;

    printf("\nBook added successfully.\n");
}

// Print Books
void printBooks(Book books[], int numBooks) {
    printf("\n--- List of Books ---\n");
    for (int i = 0; i < numBooks; i++) {
        printf("\nID: %d\n", books[i].id);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Publication Year: %d\n", books[i].year);
        printf("Number of Pages: %d\n", books[i].pages);
    }
}

// Save to File
void saveToFile(Book books[], int numBooks) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for writing.\n", FILENAME);
        return;
    }

    fwrite(&numBooks, sizeof(int), 1, file);
    fwrite(books, sizeof(Book), numBooks, file);

    fclose(file);
    printf("\nBooks saved successfully to '%s'.\n", FILENAME);
}

// Load from File
void loadFromFile(Book books[], int *numBooks) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for reading.\n", FILENAME);
        return;
    }

    fread(numBooks, sizeof(int), 1, file);
    fread(books, sizeof(Book), *numBooks, file);

    fclose(file);
    printf("\nBooks loaded successfully from '%s'.\n", FILENAME);
}

// Main Function
int main() {
    Book books[MAX_BOOKS];
    int numBooks = 0;

    int choice;
    while (1) {
        printf("\n--- Library Menu ---\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Save to File\n");
        printf("4. Load from File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character

        switch (choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                printBooks(books, numBooks);
                break;
            case 3:
                saveToFile(books, numBooks);
                break;
            case 4:
                loadFromFile(books, &numBooks);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

