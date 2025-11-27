#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100

struct Book{
    int id;
    char title[50];
    char author[50];
    bool isRead;
    bool isIssued;
};

struct Book books[MAX];
int count = 0;

void addBook();
void removeBook();
void displayBooks();
void markReadStatus();
void issueBook();
void returnBook();
void saveFile();
void loadFile();

int main(){

    loadFile();

    int choice = 0;

    do{
        printf("\n*** LIBRARY MANAGEMENT SYSTEM ***\n");
        printf("\n1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Display All Books\n");
        printf("4. Mark as Read / Unread\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Save\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            addBook();
            break;
            case 2:
            removeBook();
            break;
            case 3:
            displayBooks();
            break;
            case 4:
            markReadStatus();
            break;
            case 5:
            issueBook();
            break;
            case 6:
            returnBook();
            break;
            case 7:
            saveFile();
            break;
            case 8:
            printf("\nThanks for using my LMS!\n");
            break;
            default:
            printf("\nInvalid Choice\n");
        }
    }while(choice != 8);

    return 0;
}

void addBook(){

    if(count >= MAX){
        printf("Library is Full!");
        return;
    }

    int newID = 0;

    printf("\nEnter Book ID: ");
    scanf("%d", &newID);

    for(int i=0; i<count; i++){
        if(newID == books[i].id){
            printf("Book Already Added!\n");
            return;
        }
    }

    books[count].id = newID;
    getchar();

    printf("Enter Book Title: ");
    fgets(books[count].title, sizeof(books[count].title), stdin);
    books[count].title[strlen(books[count].title) - 1] = '\0';

    printf("Enter Author Name: ");
    fgets(books[count].author, sizeof(books[count].author), stdin);
    books[count].author[strlen(books[count].author) - 1] = '\0';

    books[count].isRead = false;
    books[count].isIssued = false;
    count++;

    printf("\nBook Added Successfully!\n");
    saveFile();

    return;
}

void removeBook(){

    int id = 0;
    bool found = false;

    printf("\nEnter ID of the book you want to remove: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++){
        if(books[i].id == id){
            for(int j=i; j<count-1; j++){
                books[j] = books[j+1];
            }
            count --;
            found = true;
            break;
        }
    }

    if(found){
        printf("Book Removed Successfully!\n");
        saveFile();
    }
    else{
        printf("Book Not Found!\n");
    }
    
    return;
}

void displayBooks(){

    if(count == 0){
        printf("\nNo Books to Display!\n");
        return;
    }

    printf("\nYour List of Books:\n");

    for(int i=0; i<count; i++){
        printf("\nID: %d\n", books[i].id);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("Read: %s\n", books[i].isRead ? "Yes" : "No");
        printf("Issued: %s\n", books[i].isIssued ? "Yes" : "No");
    }

    return;
}

void markReadStatus(){

    int id = 0;
    bool found = false;

    printf("\nEnter ID of the book you want to mark as Read: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++){
        if(books[i].id == id){
            books[i].isRead = true;
            found = true;
            break;
        }
    }

    if(found){
        printf("Book Marked as Read!\n");
        saveFile();
    }
    else{
        printf("Book not found!\n");
    }

    return;
}

void issueBook(){

    int id = 0;
    bool found = false;

    printf("\nEnter ID of the book you want to Issue: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++){
        if(books[i].id == id){
            if(books[i].isIssued){
                printf("Book is Already Issued!\n");
                return;
            }
            else{
                books[i].isIssued = true;
                found = true;
                printf("Book is Issued!\n");
                saveFile();
                return;
            }
        }
    }

    if(!found){
        printf("Book not found!\n");
    }

    return ;
}

void returnBook(){

    int id = 0;
    bool found = false;

    printf("\nEnter ID of the book you want to Remove: ");
    scanf("%d", &id);

    for(int i=0; i<count; i++){
        if(books[i].id == id){
            if(books[i].isIssued){
                books[i].isIssued = false;
                found = true;
                printf("Book Removed!\n");
                saveFile();
                return;
            }
            else{
                printf("Book wasn't Issued!\n");
                return;
            }
        }
    }

    if(!found){
        printf("Book not found!\n");
    }

    return ;
}

void saveFile(){

    FILE *writeFile = fopen("library.txt", "w");

    if(writeFile == NULL){
        printf("Error opening file!\n");
        return;
    }

    fprintf(writeFile, "%d\n", count);

    for(int i = 0; i < count; i++){
        fprintf(writeFile, "%d|%s|%s|%d|%d\n", books[i].id, books[i].title, books[i].author, books[i].isRead, books[i].isIssued);
    }

    fclose(writeFile);
    printf("\nLibrary Saved Successfully!\n");

    return;
}

void loadFile(){

    FILE *readFile = fopen("library.txt", "r");

    if (readFile == NULL) {
        printf("Couldn't read the file!");
        return;
    }

    fscanf(readFile, "%d\n", &count);

    for(int i=0; i<count; i++){
        fscanf(readFile, "%d|%49[^|]|%49[^|]|%d|%d\n", &books[i].id, &books[i].title, &books[i].author, &books[i].isRead, &books[i].isIssued);
    }

    fclose(readFile);
    return;
}