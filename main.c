#include "cache_simulator.h"

int  main(){

    cacheLine_t    m_cacheLine[N_SETS][N_WAYS];
    testvect_t     testvec[TESTVECTOR];
    unsigned int   num_hits=0;
    unsigned int   num_miss=0;
    unsigned int   num_evict=0;
    cacheLine_t    *retPtr;
    int            rand_way,find_way;
    cacheLine_t    cachePkt;
    int            i;
    int            cache_idx;

    init_cache(m_cacheLine);
    init_testvec(testvec, (sizeof(testvec)/sizeof(testvect_t)));

    //print_cache(cacheLine, N_SETS, N_WAYS);
    
    printf("Program Starting ...............\n");
    printf("Init all test vectors\n");
    print_testvec(testvec, (sizeof(testvec)/sizeof(testvect_t)));

    //Perform the Cache Lookup
    for(i=0;i<TESTVECTOR;i++){
        cache_idx = find_index(testvec[i].addr);
        retPtr = lookup_cache(m_cacheLine,testvec[i].addr,cache_idx);
        if(retPtr != NULL){ 
            //Hit
            num_hits = num_hits + 1;
            printf("Program Entering Hit loop ...............\n");
        }else{
            //Miss
            printf("Program Entering Miss loop ...............\n");
            num_miss = num_miss + 1;
           
            if(isWayFull(m_cacheLine,cache_idx) == 1){
                num_evict = num_evict + 1;
                rand_way = pickRandWay(); 
                cachePkt.addr = testvec[i].addr;
                if(strcmp(testvec[i].cmd,"RD") == 0){
                    cachePkt.state = "SC";
                }else{
                    cachePkt.state = "UD";
                }
                cachePkt.index = cache_idx;
                cachePkt.way   = rand_way;

                printf("Deleting a cacheline\n");
                print_cache(m_cacheLine);

                add_cacheline(m_cacheLine,cache_idx,rand_way,&cachePkt);

                printf("Adding a cacheline\n");
                print_cache(m_cacheLine);
            }else{
                find_way = findIWay(m_cacheLine,cache_idx);
                cachePkt.addr = testvec[i].addr;
                if(strcmp(testvec[i].cmd,"RD") == 0){
                    cachePkt.state = "SC";
                }else{
                    cachePkt.state = "UD";
                }
                cachePkt.index = cache_idx;
                assert(find_way>=0);
                cachePkt.way   = find_way;
                add_cacheline(m_cacheLine,cache_idx,find_way,&cachePkt);
                printf("Adding a cacheline \n");
                print_cache(m_cacheLine);
            }
        }
    }

    printf("End of Program\n");
    printf("No of Hits:%d, No of Miss:%d, No of Evicts:%d \n",num_hits, num_miss, num_evict);
    
    return 0;
}
