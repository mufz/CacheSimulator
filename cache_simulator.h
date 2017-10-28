#ifndef CACHE_SIMULATOR_H
#define CACHE_SIMULATOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define N_SETS 4
#define N_WAYS 4
#define TESTVECTOR 20
#define INDEX_LSB 6
#define INDEX_MSB 7
//Basic Cache Structure 
typedef struct {
    int         addr;
    char       *state; 
    int         index;
    int         way;
    int         data;
} cacheLine_t;

typedef struct {
    int         addr;
    char       *cmd; 
    int         index;
} testvect_t;


void init_cache(cacheLine_t (*ptr) [N_WAYS]);
void print_cache(cacheLine_t (*ptr) [N_WAYS]);
cacheLine_t* lookup_cache(cacheLine_t (*ptr) [N_WAYS],int lookup_addr, int lookup_index);
void add_cacheline(cacheLine_t (*ptr) [N_WAYS], int index, int way, cacheLine_t *padd);
int isWayFull(cacheLine_t (*ptr) [N_WAYS], int index);
int findIWay(cacheLine_t (*ptr) [N_WAYS], int index);
int pickRandWay();
void init_testvec(testvect_t *ptr,size_t size);
void print_testvec(testvect_t *ptr,size_t size);

int createmask(int a, int b);
int find_index(int addr);

#endif
