//
//  main.c
//  newman_ziff
//
//  Created by vitor on 01/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include "network.h"
#include "percolation.h"

int **nbr, *distance;
int *Z, L, N;
double pB, pG, delta, p;
gsl_rng *r;
double ranD;

int main(int argc, const char * argv[]){
    
    int i, TC, size_max, na, NA;
    double dp, pGmax, S;
    
    if(argc!=7){
        printf("Use: <%s> <L> <delta> <pB> <dp> <pGmax> <NA>\n",argv[0]);
        return(1);
    } 
    
    L = atoi(argv[1]);
    NA= atoi(argv[6]);
    
    delta = atof(argv[2]);         
    pB = atof(argv[3]);
    dp = atof(argv[4]);
    pGmax= atof(argv[5]); 
    
    
    if((r = gsl_rng_alloc(gsl_rng_mt19937)) == NULL) {
        printf("ERROR: Could not create random number generator\n");
        exit(1);
    }
    gsl_rng_set(r, 12312377);
    
    N=L*L;
    
    memory_alloc();
    initBfs();
    
    for (pG=pB; pG<pGmax; pG+=dp) {
        S=0;
        for (na=0; na<NA; na++) {
            
            for (i=0; i<N; i++) { Z[i]=0; distance[i]=0;}
            
            size_max=0;
            config_gen();
            
            for (i=0; i<N; i++) {
                if(!(distance[i]))
                    TC = bfs(i);
                if(size_max<TC)
                    size_max = TC;
            }
            
            S+=(double)size_max/N;
            
            
        }
        
        printf("%lf %lf\n", pG, S/NA);
    }
    
    
    gsl_rng_free (r);
    return (0);
}

