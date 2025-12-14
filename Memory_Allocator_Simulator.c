#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_SIZE (1024 * 1024)
#define BLOCK_SIZE sizeof(Block)

typedef struct nextBlocks{
    size_t size;
    int free;
    struct nextBlocks *next;
}Block;

static unsigned char heap[HEAP_SIZE];
static Block *freeList = NULL;

static void init_heap(void){

    freeList = (Block *)heap;
    freeList -> size = HEAP_SIZE - BLOCK_SIZE;
    freeList -> free = 1;
    freeList -> next = NULL;
}

void split_block(Block *block, size_t size){

    Block *newBlock = (Block *)((char *)block + BLOCK_SIZE + size);
    newBlock -> size = block -> size - size - BLOCK_SIZE;
    newBlock -> free = 1;
    newBlock -> next = block -> next;
    block -> size = size;
    block -> free = 0;
    block -> next = newBlock;
}

Block *find_free_block(size_t size){

    Block *current = freeList;

    while(current){
        if(current -> free && current -> size >= size){
            return current;
        }
        current = current -> next;
    }
    return NULL;
}

void *my_malloc(size_t size){

    if(size == 0){
        return NULL;
    }

    if(!freeList){
        init_heap();
    }

    Block *block = find_free_block(size);

    if(!block){
        printf("Memory Allocation Failed!\n");
        return NULL;
    }

    if(block -> size >= size + BLOCK_SIZE + 8){
        split_block(block, size);
    }
    else{
        block -> free = 0;
    }
    return (char *)block + BLOCK_SIZE;  
}

void merge(void){

    Block *current = freeList;

    while(current && current -> next){
        if(current -> free && current -> next -> free){
            current -> size += BLOCK_SIZE + current -> next -> size;
            current -> next = current -> next -> next;
        }
        else{
            current = current -> next;
        }
    }
}

void my_free(void *ptr){

    if(!ptr){
        return;
    }

    Block *block = (Block *)((char *)ptr - BLOCK_SIZE);
    block -> free = 1;
    merge();
}

void show_heap(void){

    Block *current = freeList;

    printf("\nHeap State:\n");
    
    while(current){
        printf("Block @ %p | size: %zu | %s\n", (void *)current, current -> size, current -> free ? "FREE" : "USED");
        current = current -> next;
    }
}

int main(void){

    void *a = my_malloc(100);
    void *b = my_malloc(200);
    void *c = my_malloc(300);

    show_heap();

    my_free(b);
    printf("\nAfter freeing block b:\n");
    show_heap();

    void *d = my_malloc(150);

    printf("\nAfter alloacting block d (150 bytes):\n");
    show_heap();    

    my_free(a);
    my_free(c);
    my_free(d);

    printf("\nAfter freeing all blocks:\n");
    show_heap();

    return 0;
}