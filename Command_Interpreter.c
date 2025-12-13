#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>

#define INITIAL_CAPACITY 8
#define MAX_PATH_LENGTH 1024

typedef int (*command_func)(int argc, char **argv);

char *readLine(void){

    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if(!buffer){
        perror("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }

    int c;
    while((c = getchar()) != '\n' && c != EOF){
        buffer[length++] = (char)c;

        if(length+1 >= capacity){
            capacity *= 2;
            char *temp = realloc(buffer, capacity);
            if(!temp){
                perror("Memory Reallocation Failed!\n");
                exit(EXIT_FAILURE);
            }
            buffer = temp;
        }
    }
    buffer[length] = '\0';
    return buffer;
}

char **split_line(char *line, int *argc){

    int capacity = INITIAL_CAPACITY;
    char *token;
    char **argv = malloc(capacity * sizeof(char *));

    if(!argv){
        perror("Memory Allocation Failed!\n");
        exit(EXIT_FAILURE);
    }

    *argc = 0;
    token = strtok(line, " \t");

    while(token){
        argv[(*argc)++] = _strdup(token);

        if(*argc >= capacity){
            capacity *= 2;
            char **temp = realloc(argv, capacity * sizeof(char *));

            if(!temp){
                perror("Memory Reallocation Failed!\n");
                exit(EXIT_FAILURE);
            }
            argv = temp;
        }
        token = strtok(NULL, "\t");
    }
    argv[*argc] = NULL;
    return argv;
}

void free_argv(char **argv){

    for(int i = 0; argv[i]; i++){
        free(argv[i]);
    }
    free(argv);
}

int cmd_exit(int argc, char **argv){

    (void)argc;
    (void)argv;
    return 1;
}

int cmd_pwd(int argc, char **argv){

    (void)argc;
    (void)argv;

    char cwd[MAX_PATH_LENGTH];
    if(_getcwd(cwd, sizeof(cwd))){
        printf("%s\n", cwd);
    }
    return 0;
}

int cmd_cd(int argc, char **argv){

    if(argc < 2){
        fprintf(stderr, "cd: missing arguments\n");
        return 0;
    }

    if(_chdir(argv[1]) != 0){
        perror("cd");
    }
    return 0;
}

int cmd_ls(int argc, char **argv){
    
    (void)argc;
    (void)argv;

    WIN32_FIND_DATA data;
    HANDLE h = FindFirstFile("*", &data);

    if(h == INVALID_HANDLE_VALUE){
        return 0;
    }

    do{
        printf("%s ", data.cFileName);
    }while(FindNextFile(h, &data));

    printf("\n");
    FindClose(h);
    return 0;
}

typedef struct{
    const char *name;
    command_func func;
}Commands;

Commands command_table[] = {
    {"exit", cmd_exit},
    {"pwd", cmd_pwd},
    {"cd", cmd_cd},
    {"ls", cmd_ls},
    {NULL, NULL}
};

int main(void){

    while(1){
        char cwd[MAX_PATH_LENGTH];
        _getcwd(cwd, sizeof(cwd));
        printf("%s> ", cwd);

        char *line = readLine();
        int argc;
        char **argv = split_line(line, &argc);
        free(line);

        if(argc == 0){
            free_argv(argv);
            continue;
        }

        int lookup = 0;
        for(int i = 0; command_table[i].name; i++){
            if(strcmp(argv[0], command_table[i].name) == 0){
                if(command_table[i].func(argc, argv)){
                    free_argv(argv);
                    return 0;
                }
                lookup = 1;
                break;
            }
        }
        if(!lookup){
            printf("Unknown Command: %s\n", argv[0]);
        }
        free_argv(argv);
    }
}