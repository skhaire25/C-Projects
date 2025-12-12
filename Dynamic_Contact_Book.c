#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    int id;
    char *name;
    char *phone;
    char *email;
}Contacts;

static Contacts *contact = NULL;
static size_t count = 0;
static size_t capacity = 0;

void clearBuffer();
void checkCapacity();
char *readLine(void);
char *string_dup(const char *s);
void addContact();
void viewContacts();
int searchByID(int id);
int searchByName(const char *name);
int caseInsensitive(const char *a, const char *b);
void updateContact();
int dupPhone(const char *newPhone);
int dupEmail(const char *newEmail);
void deleteContact();
static void saveFile();
static void loadFile();
static void freeContact(Contacts *c);
static void freeAllContacts();
static void sortByName();


int main(){

    loadFile();

    int choice = 0;
    int id = 0;

    do{
        printf("\n***CONTACT BOOK***\n");
        printf("1. Add Contact\n2. View All Contacts\n3. Search Contact by ID\n4. Search Contact by Name\n5. Update Contact\n6. Delete Contact\n7. Sort Contact by Name\n8. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) != 1){
            printf("Invalid Input!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch(choice){

            case 1:
            addContact();
            break;

            case 2:
            viewContacts();
            break;

            case 3:
            printf("Enter ID to search: ");
            if(scanf("%d", &id) != 1){
                printf("Invalid ID\n");
                clearBuffer();
                break;
            }
            clearBuffer();

            int idx = searchByID(id);
            if(idx >= 0){
                printf("Found: ID: %d | Name: %s | Phone: %s | Email: %s\n", 
                       contact[idx].id, contact[idx].name, contact[idx].phone, contact[idx].email);
            }
            else{
                printf("Contact Not Found!\n");
            }
            break;

            case 4:
            printf("Enter name to search: ");
            char *name = readLine();
            if(!name || strlen(name) == 0){
                printf("Invalid Name!\n");
                free(name);
                break;
            }

            int idy = searchByName(name);
             if(idy >= 0){
                printf("Found: ID: %d | Name: %s | Phone: %s | Email: %s\n", 
                       contact[idy].id, contact[idy].name, contact[idy].phone, contact[idy].email);
            }
            else{
                printf("Contact Not Found!\n");
            }
            free(name);
            break;

            case 5:
            updateContact();
            break;

            case 6:
            deleteContact();
            break;

            case 7:
            sortByName();
            break;

            case 8:
            printf("\nExiting...");
            break;

            default:
            printf("Invalid Choice!");
        }
    }while(choice != 8);

    return 0;
}

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF){
        
    }
    return;
}

void checkCapacity(){
    if(count < capacity){
        return;
    }
    
    size_t newCapacity = (capacity == 0) ? 4 : capacity*2;

    if(capacity == 0){
        contact = calloc(newCapacity, sizeof(Contacts));
        if(contact == NULL){
            fprintf(stderr, "\nMemory Allocation Failed\n");
            return;
        }
    }
    else{
        Contacts *temp =realloc(contact, newCapacity*sizeof(Contacts));
        if(temp == NULL){
            fprintf(stderr,"\nMemory Reallocation Failed\n");
            return;
        }
        contact = temp;
    }
    capacity = newCapacity;
}

char *readLine(void){
    size_t cap = 128;
    size_t len = 0;
    char *buf = malloc(cap);
    if(buf == NULL){
        fprintf(stderr, "\nMemory Allocation Failed!\n");
        return NULL;
    }

    int ch;
    while((ch = getchar()) != '\n' && ch != EOF){
        buf[len++] = (char)ch;
        if(len + 1 >= cap){
            cap *= 2;
            char *temp = realloc(buf, cap);
            if(!temp){
                free(buf);
                fprintf(stderr, "\nMemory Reallocation Failed!\n");
                return NULL;
            }
            buf = temp;
        }
    }

    buf[len] = '\0';
    if(len == 0 && ch == EOF){
        free(buf);
        return NULL;
    }
    return buf;
}

char *string_dup(const char *s){
    if(s == NULL){
        return NULL;
    }

    size_t n = strlen(s) + 1;
    char *temp = malloc(n);
    if(!temp){
        fprintf(stderr, "\nMemory Allocation Failed!\n");
        return NULL;
    }
    memcpy(temp, s, n);
    return temp;
}

void addContact(){

    checkCapacity();

    int id = 0;
    printf("\nEnter Contact ID: ");
    if(scanf("%d", &id) != 1){
            printf("Invalid Input!\n");
            clearBuffer();
            return;
        }
        clearBuffer();

    if(id < 0){
        printf("ID can't be negative!\n");
        return;
    }

    if(searchByID(id) != -1){
        printf("Contact ID %d already exists\n", id);
        return;
    }
    contact[count].id = id;

    printf("\nEnter Name: ");
    char *name = readLine();
    if(!name || strlen(name) == 0){
        printf("Name can't be empty.\n");
        free(name);
        return;
    }
    contact[count].name = name;

    printf("\nEnter Phone: ");
    char *phone = readLine();
    
    if(dupPhone(phone) != -1){
        printf("Phone number already exists.\n");
        free(phone);
        return;
    }
    else{
        free(contact[count].phone);
        contact[count].phone = phone ? phone : string_dup("");
    }

    printf("\nEnter Email: ");
    char *email = readLine();

    if(dupEmail(email) != -1){
        printf("Email number already exists.\n");
        free(email);
        return;
    }
    else{
        free(contact[count].email);
        contact[count].email = email ? email : string_dup("");
    }

    count++;
    printf("Contact added successfully.\n");
    saveFile();
    return;
}

void viewContacts(){

    if(count == 0){
        printf("\nNo Contacts to display\n");
        return;
    }

    printf("\nYOUR CONTACTS\n");
    for(size_t i = 0; i < count; i++){
        printf("%zu> ID: %d | Name: %s | Phone: %s | Email: %s\n", i+1, 
               contact[i].id,
               contact[i].name ? contact[i].name : "NULL",
               contact[i].phone ? contact[i].phone : "NULL",
               contact[i].email ? contact[i].email : "NULL");
    }
    return;
}

int searchByID(int id){

    for(size_t i = 0; i < count; i++){
        if(contact[i].id == id){
            return (int)i;
        }
    }
    return -1;
}

int searchByName(const char *name){

    for(size_t i = 0; i < count; i++){
        if(contact[i].name && caseInsensitive(contact[i].name, name) == 0){
            return (int)i;
        }
    }
    return -1;
}

int caseInsensitive(const char *a, const char *b){

    while(*a && *b){
        int ca = tolower((unsigned char) *a);
        int cb = tolower((unsigned char) *b);
        if(ca != cb){
            return (ca < cb) ? -1 : 1;
        }
        a++; 
        b++;
    }
    if(*a){
        return 1;
    }
    if(*b){
        return -1;
    }
    return 0;
}

void updateContact(){

    if(count == 0){
        printf("\nNo Contacts to Update.\n");
        return;
    }

    int id = 0;
    printf("\nEnter ID of Contact you wanna update: ");
    if(scanf("%d", &id) != 1){
        printf("Invlaid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    int idx = searchByID(id);
    if(idx < 0){
        printf("Contact Not Found!\n");
        return;
    }

    int choice = 0;
    do{
        printf("\nUpdating Contact ID: %d\n", id);
        printf("1. Update Name\n2. Update Phone\n3. Update Email\n4. Return to Menu\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) != 1){
            printf("Invalid Input!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        if(choice == 1){
            printf("\nEnter the updated name: ");
            char *name = readLine();
            if(!name || strlen(name) == 0){
                printf("Name can't be empty!\n");
                free(name);
            }
            else{
                free(contact[idx].name);
                contact[idx].name = name;
                printf("Name updated successfully.\n");
                saveFile();
            }
        }
        else if(choice == 2){
            printf("\nEnter the updated phone: ");
            char *phone = readLine();

            if(dupPhone(phone) != -1){
                printf("Phone number already exists.\n");
                free(phone);
            }
            else{
                free(contact[idx].phone);
                contact[idx].phone = phone ? phone : string_dup("");
                printf("Phone updated successfully.\n");
                saveFile();
            }
        }
        else if(choice == 3){
            printf("\nEnter the updated email: ");
            char *email = readLine();
            
            if(dupEmail(email) != -1){
                printf("Email number already exists.\n");
                free(email);
            }
            else{
                free(contact[idx].email);
                contact[idx].email = email ? email : string_dup("");
                printf("Email updated successfully.\n");
                saveFile();
            }
        }
        else if(choice == 4){
            break;
        }
        else{
            printf("Invalid Choice!\n");
        }

    }while(choice != 4);

    return;
}

int dupPhone(const char *newPhone){

    for(size_t i = 0; i < count; i++){
        if(contact[i].phone && strcmp(contact[i].phone, newPhone) == 0){
            return (int)i;
        }
    }
    return -1;
}

int dupEmail(const char *newEmail){

    for(size_t i = 0; i < count; i++){
        if(contact[i].email && strcmp(contact[i].email, newEmail) == 0){
            return (int)i;
        }
    }
    return -1;
}

void deleteContact(){

    if(count == 0){
        printf("\nNo Contacts to Delete.\n");
        return;
    }

    int id = 0;
    printf("\nEnter ID of Contact you wanna delete: ");
    if(scanf("%d", &id) != 1){
        printf("Invlaid ID!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    int idx = searchByID(id);
    if(idx < 0){
        printf("\nContact Not Found!\n");
        return;
    }

    freeContact(&contact[idx]);

    for(size_t j = (size_t)idx; j+1 < count; j++){
        contact[j] = contact[j+1];
    }

    contact[count-1].id = 0;
    contact[count-1].name = NULL;
    contact[count-1].phone = NULL;
    contact[count-1].email = NULL;

    count--;
    printf("\nContact deleted successfully.\n");
    saveFile();
    return;
}

static void saveFile(){

    FILE *wf = fopen("Contacts.txt","w");

    if(wf == NULL){
        perror("Error opening file!\n");
        return;
    }

    fprintf(wf, "%zu\n", count);

    for(int i = 0; i < count; i++){
        fprintf(wf, "%d|%s|%s|%s\n", contact[i].id, 
                contact[i].name ? contact[i].name : "", 
                contact[i].phone ? contact[i].phone : "", 
                contact[i].email ? contact[i].email : "");
    }

    fclose(wf);
    printf("\nSaved to Library Successfully!\n");
    return;
}

static void loadFile(){

    FILE *rf = fopen("Contacts.txt", "r");

    if (rf == NULL) {
        perror("Couldn't read the file!\n");
        return;
    }

    size_t cnt = 0;
    if(fscanf(rf, "%zu\n", &cnt) != 1){
        fclose(rf);
        return;
    }

    if(cnt == 0){
        fclose(rf);
        return;
    }

    contact = calloc(cnt, sizeof(Contacts));
    if(!contact){
        fprintf(stderr, "\nMemory Allocation Failed!\n");
        return;
    }
    capacity = cnt;
    count = 0;

    char buf[4096];
    for(size_t i = 0; i < cnt; i++){
        if(fgets(buf, sizeof(buf), rf) == NULL){
            break;
        }

        char *newLine = strchr(buf, '\n');
        if(newLine){
            *newLine = '\0';
        }
        
        char *idToken = strtok(buf, "|");
        char *nameToken = idToken ? strtok(NULL, "|") : NULL;
        char *phoneToken = nameToken ? strtok(NULL, "|") : NULL;
        char *emailToken = phoneToken ? strtok(NULL, "|") : NULL;

        if(!idToken){
            continue;
        }

        int id = atoi(idToken);
        contact[count].id = id;
        contact[count].name = nameToken ? string_dup(nameToken) : string_dup("");
        contact[count].phone = phoneToken ? string_dup(phoneToken) : string_dup("");
        contact[count].email = emailToken ? string_dup(emailToken) : string_dup("");
        
        count++;
    }
    fclose(rf);
    return;
}

static void freeContact(Contacts *c){

    if(!c){
        return;
    }

    free(c->name);
    free(c->phone);
    free(c->email);
    c->name = c->phone = c->email = NULL;

    return;
}

static void freeAllContacts(){

    if(!contact){
        return;
    }

    for(size_t i = 0; i < count; i++){
        freeContact(&contact[i]);
    }

    free(contact);
    contact = NULL;
    count = 0;
    capacity = 0;

    return;
}

static void sortByName(){

    if(count == 0){
        printf("\nNo Contacts to Sort.\n");
        return;
    }
    else if(count == 1){
        printf("\nYOUR CONTACTS\n");
        for(size_t i = 0; i < count; i++){
        printf("%zu> ID: %d | Name: %s | Phone: %s | Email: %s\n", i+1, 
            contact[i].id,
            contact[i].name ? contact[i].name : "NULL",
            contact[i].phone ? contact[i].phone : "NULL",
            contact[i].email ? contact[i].email : "NULL");
        }
        return;
    }
    else{
        for(size_t i = 1; i < count; i++){
            Contacts key = contact[i];
            size_t j = i;
            while(j > 0 && caseInsensitive(contact[j-1].name, key.name) > 0){
                contact[j] = contact[j-1];
                j--;
            }
            contact[j] = key;
        }
        printf("\nContacts sorted by name:\n");
        for(size_t i = 0; i < count; i++){
        printf("%zu> ID: %d | Name: %s | Phone: %s | Email: %s\n", i+1, 
            contact[i].id,
            contact[i].name ? contact[i].name : "NULL",
            contact[i].phone ? contact[i].phone : "NULL",
            contact[i].email ? contact[i].email : "NULL");
        }
        saveFile();
    }
    return;
}