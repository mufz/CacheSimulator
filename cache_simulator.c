#include "cache_simulator.h"

void init_cache(cacheLine_t (*ptr) [N_WAYS]){
    int i,m;
    for(i=0;i<N_SETS;i++){
        for(m=0;m<N_WAYS;m++){
            ptr[i][m].addr  = 0;
            ptr[i][m].state = "IX";
            ptr[i][m].index = i;
            ptr[i][m].way   = m;
            ptr[i][m].data  = 0;
        }
    }

}


void print_cache(cacheLine_t (*ptr) [N_WAYS]){
    int i,m;
    for(i=0;i<N_SETS;i++){
        for(m=0;m<N_WAYS;m++){
            printf("ADDR:%d, State:%s, Data:%d Index:%d and Way:%d \n",
             ptr[i][m].addr,ptr[i][m].state,ptr[i][m].data,i,m); 
        }
    }

}

cacheLine_t* lookup_cache(cacheLine_t (*ptr) [N_WAYS],int lookup_addr, int lookup_index){
    int m;
    for(m=0;m<N_WAYS;m++){
        if((ptr[lookup_index][m].addr == lookup_addr) && 
           (strcmp(ptr[lookup_index][m].state,"IX"))){
            return &(ptr[lookup_index][m]);
        }
    }
    
    return NULL;
}


void add_cacheline(cacheLine_t (*ptr) [N_WAYS], int index, int way, cacheLine_t *padd){
  
    assert(padd != NULL);
    ptr[index][way].addr  = padd->addr;
    ptr[index][way].state = padd->state;
    ptr[index][way].index = padd->index;
    ptr[index][way].way   = padd->way;
    //ptr[index][way].data  = padd->data;
        
}

int isWayFull(cacheLine_t (*ptr) [N_WAYS], int index){
    char *string;
    string = "IX";
    int m;
    for(m=0;m<N_WAYS;m++){
        if(strcmp(ptr[index][m].state,string)==0){
            return 0;
        }
    }
    return 1;
}

int findIWay(cacheLine_t (*ptr) [N_WAYS], int index){
    char *string;
    string = "IX";
    int m;
    for(m=0;m<N_WAYS;m++){
        if(strcmp(ptr[index][m].state,string) == 0){
            return m;
        }
    }
    return -1;
}


int pickRandWay(){
    int s = 0;

    s = rand() % N_WAYS;
    return s;
}

void init_testvec(testvect_t *ptr,size_t size){
    int i;

    for(i=0;i<size;i++){
        ptr[i].addr  = rand() % 500;
        ptr[i].cmd   = "RD";
        ptr[i].index = rand() % N_SETS;
    }
}

void print_testvec(testvect_t *ptr,size_t size){
    int i;

    assert(ptr != NULL);
    for(i=0;i<size;i++){
        printf("Addr:%d and CMD:%s Index:%d \n", ptr[i].addr, ptr[i].cmd,ptr[i].index);
    }
}


int createmask(int a, int b){ 
    int r=0; 
    int i;
    for(i=a;i<=b;i++){
        r |= 1 << i;
    }   
    return r;
}

//Program considers a cache of 64 Bytes
//2 beats are used to represent critical beat i.e 
//For 128-bit bus you will have 4 beats of 16 Bytes
//2-bit will let you know which beat you are.
int find_index(int addr){
    int result;
    int mask;
    
    mask = createmask(INDEX_LSB,INDEX_MSB);
    result = (addr>>6) & (mask>>6);
    return result;
}

