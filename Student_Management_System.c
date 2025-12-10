#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int id;
    char name[100];
    int roll;
    float marks;
    bool status;
}Student;

Student *students = NULL;
int count = 0;
int capacity = 0;

void clearBuffer();
void checkCapacity();
void addStudents();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveFile();
void loadFile();
void newID();
void newName();
void newRoll();
void newMarks();
void studentStatus();

int main(){

    loadFile();
    
    int choice = 0;
    
    do{
        printf("\n***STUDENT MANAGEMENT SYSTEM***\n");
        printf("1. Add Student\n2. View All Students\n3. Search Students by ID\n4. Update Student\n5. Delete Student\n6. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) != 1){
            printf("Input valid ID!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch(choice){
            case 1:
            addStudents();
            break;
            
            case 2:
            viewStudents();
            break;

            case 3:
            searchStudent();
            break;

            case 4:
            updateStudent();
            break;

            case 5:
            deleteStudent();
            break;

            case 6:
            printf("\nExiting...");
            break;
            
            default:
            printf("Invalid choice!\n");
        }

    }while(choice != 6);

    free(students);
    return 0;
}

void clearBuffer(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF){
        //discard 
    }
}

void checkCapacity(){
    if(count >= capacity){
        int newCapacity = (capacity == 0) ? 2 : capacity*2;
        Student *temp = realloc(students, newCapacity * sizeof(Student));
        if (temp == NULL){
            printf("\nMemory allocation failed!");
            return;
        }
        students = temp;
        capacity = newCapacity;
    }
}

void addStudents(){

    checkCapacity();

    int newID = 0, newRoll = 0;
    float newMarks = 0.0;

    printf("\nEnter stduent's ID: ");
    if(scanf("%d", &newID) != 1){
        printf("Input valid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for(int i = 0; i < count; i++){
        if(newID == students[i].id){
            printf("Student already added!\n");
            return;
        }
    }
    students[count].id = newID;

    printf("Enter student's name: ");
    if(fgets(students[count].name, sizeof(students[count].name), stdin) == NULL){
        printf("Failed to read name!\n");
        return;
    }
    students[count].name[strcspn(students[count].name, "\n")] = '\0';
    if(strlen(students[count].name) == 0){
        printf("Invalid Name! Name can't be empty.\n");
        return;
    }

    printf("Enter student's roll no.: ");
    if(scanf("%d", &newRoll) != 1){
        printf("Input valid Roll number!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for(int j = 0; j < count; j++){
        if(newRoll == students[j].roll){
            printf("Roll number already added!\n");
            return;
        }
    }
    if(newRoll < 0){
        printf("Invalid Roll number! It must be positive.\n");
        return;
    }
    students[count].roll = newRoll;

    printf("Enter student's marks: ");
    if(scanf("%f", &newMarks) != 1){
        printf("Input valid marks!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    if(newMarks < 0 || newMarks > 100){
        printf("Invalid marks! Must be between 0 and 100.\n");
        return;
    }
    students[count].marks = newMarks;

    if(students[count].marks < 35){
        students[count].status = false;
    }
    else{
        students[count].status = true;
    }
    
    count++;
    printf("\nStudent Added Successfully!\n");
    saveFile();

    return;
}

void viewStudents(){

    if(count == 0){
        printf("\nNo Students Added!\n");
        return;
    }

    for(int i=0; i < count; i++){
        printf("\nStudent ID: %d\n", students[i].id);
        printf("Student name: %s\n", students[i].name);
        printf("Student roll no.: %d\n", students[i].roll);
        printf("Student marks: %.2f\n", students[i].marks);
        printf("Student Status: %s\n", students[i].status ? "Pass" : "Fail");
    }

    return;
}

void searchStudent(){

    if(count == 0){
        printf("\nNo Students to Search!\n");
        return;
    }

    int id = 0;

    printf("\nEnter ID of student you wanna search: ");
    if(scanf("%d", &id) != 1){
        printf("Input valid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for(int i = 0; i < count; i++){
        if(students[i].id == id){
            printf("Student name: %s\n", students[i].name);
            printf("Student roll no.: %d\n", students[i].roll);
            printf("Student marks: %.2f\n", students[i].marks);
            printf("Student Status: %s\n", students[i].status ? "Pass" : "Fail");
            return;
        }
        
    }
    printf("Student not found!\n");
    return;
}

void updateStudent(){

    if(count == 0){
        printf("\nNo Students Update!\n");
        return;
    }

    int choice = 0;

    do{

        printf("\n1. Update ID\n2. Update Name\n3. Update roll number\n4. Update marks\n5. Return to Menu\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) != 1){
            printf("Input valid ID!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch(choice){

            case 1:
            newID();
            break;

            case 2:
            newName();
            break;

            case 3:
            newRoll();
            break;

            case 4:
            newMarks();
            break;

            case 5:
            //exit
            break;

            default:
            printf("Invalid Choice!\n");
            }
        }while(choice != 5);
}

void deleteStudent(){

    if(count == 0){
        printf("\nNo Students to Delete!\n");
        return;
    }

    int id = 0;
    
    printf("\nEnter ID of Student you wanna remove: ");
    if(scanf("%d", &id) != 1){
        printf("Input valid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for(int i = 0; i < count; i++){
        if(students[i].id == id){
            for(int j=i; j < count-1; j++){
                students[j] = students[j+1];
            }
            count--;
            printf("Student Removed!\n");
            saveFile();
            return;
        }
    }
    printf("Student not found!\n");
    return;
}

void saveFile(){

    FILE *wf = fopen("Student.dat","wb");

    if(wf == NULL){
        printf("Can't save to file!");
        return;
    }

    fwrite(&count, sizeof(int), 1, wf);

    if(count > 0){
        fwrite(students, sizeof(Student), count, wf);
    }

    printf("Student info successfully saved.\n");
    fclose(wf);

    return;
}

void loadFile(){

    FILE *rf = fopen("Student.dat","rb");

    if(rf == NULL){
        //can't load file
        return;
    }

    if(fread(&count, sizeof(int), 1, rf) != 1){
        fclose(rf);
        return;
    }

    if(count > 0){
        capacity = count;
        students = malloc(capacity * sizeof(Student));
        if(students == NULL){
            //memory allocation failed
            fclose(rf);
            exit(1);
        }

        if(fread(students, sizeof(Student), count, rf) != (size_t)count){
            //error reading
            count = 0;
        }
    }

    fclose(rf);
    return;
}

void newID(){

    int id = 0;

    printf("\nEnter current ID of student to update ID: ");
    if(scanf("%d", &id) != 1){
        printf("Input valid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            int newID = 0;
            printf("Enter updated ID of student: ");
            if(scanf("%d", &newID) != 1){
                printf("Input valid ID!\n");
                clearBuffer();
                return;
            }
            clearBuffer();

            for(int j = 0; j < count; j++){
                if(newID == students[j].id){
                   printf("ID already exist!\n");
                   return;
                }
            }
            students[i].id = newID;
            printf("ID Successfully Updated!\n");
            saveFile();
            return;
        }
    }
    printf("Student not found!\n");
    return;
}

void newName(){

    int id = 0;
    char newName[100] = {0};

    printf("\nEnter the ID of student to update name: ");
    if(scanf("%d", &id) != 1){
        printf("Input valid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            
            printf("Enter the updated student name: ");
            if(fgets(newName, sizeof(newName), stdin) == NULL){
                printf("Failed to read name!\n");
                return;
            }
            newName[strcspn(newName, "\n")] = '\0';

            if(strlen(newName) == 0){
                printf("Invalid Name! Name can't be empty.\n");
                return;
            }
            strcpy(students[i].name, newName);
            printf("Name Successfully Updated!\n");
            saveFile();
            return;
        }
    }
    printf("Student not found!\n");
    return;
}

void newRoll(){

    int id = 0;

    printf("\nEnter the ID of student to update roll no.: ");
    if(scanf("%d", &id) != 1){
        printf("Input valid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            int newRoll = 0;
            printf("Enter updated roll number of student: ");
            if(scanf("%d", &newRoll) != 1){
                printf("Input valid Roll number!\n");
                clearBuffer();
                return;
            }
            clearBuffer();

            for(int j = 0; j < count; j++){
                if(newRoll == students[j].roll){
                   printf("Roll number already exist!\n");
                   return;
                }
            }

            if(newRoll < 0){
                printf("Invalid Roll number! It must be positive.\n");
                return;
            }

            students[i].roll = newRoll;
            printf("Roll number Successfully Updated!\n");
            saveFile();
            return;
        }
    }
    printf("Student not found!\n");
    return;
}

void newMarks(){

    int id = 0;

    printf("\nEnter the ID of student to update marks: ");
    if(scanf("%d", &id) != 1){
        printf("Input valid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            float newMarks = 0;
            printf("Enter updated marks of student: ");
            if(scanf("%f", &newMarks) != 1){
                printf("Input valid marks!\n");
                clearBuffer();
                return;
            }
            clearBuffer();

            if(newMarks < 0 || newMarks > 100){
                printf("Invalid Marks! Marks must be between 0 to 100\n");
                return;
            }
            students[i].marks = newMarks;

            if(students[i].marks < 35){
                students[i].status = false;
            }
            else{
                students[i].status = true;
            }

            printf("Marks Successfully Updated!\n");
            saveFile();
            return;
        }
    }
    printf("Student not found!\n");
    return;
}

void studentStatus(){

    return;
}