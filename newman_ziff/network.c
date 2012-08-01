//
//  network.c
//  newman_ziff
//
//  Created by vitor on 01/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

int **nbr;
int *Z, L, N, i, aux1, aux2;
double pB, pG, delta, ranD, p;
gsl_rng *r;

void memory_alloc(void){
    int i; 
    nbr = (int **)realloc(NULL, N * sizeof(int *));
    for(i=0;i<N;i++){
        nbr[i]=(int *)calloc(4, sizeof(int));   
    }
    Z = (int *)calloc(N, sizeof(int));
}

void add_link(int v1, int v2){
    nbr[v1][Z[v1]] = v2;
    nbr[v2][Z[v2]] = v1;    
    Z[v1]++;
    Z[v2]++;
}

void config_gen(void){
    int i, j;      aux1 = 2 * L;
    int v1, v2;

    for (i=1; i<aux1; i+=2) {   //Tiras verticais de elos horizontais
        ranD = gsl_rng_uniform(r);
        if(ranD<delta) 
            p = pB;
        else           
            p = pG;
    
        for (j=i; j<2*N; j+=aux1) {
            ranD = gsl_rng_uniform(r);
            if (ranD<p) {
                v1 = j/2;
                v2 = v1 + 1 - !((v1 + 1)%L) * L;
                
                add_link(v1, v2);
            }
        }
    }
    
    
    for (i=0; i<2*N; i+=aux1) {   //Tiras horizontais de elos verticais
        ranD = gsl_rng_uniform(r);
        if(ranD<delta) 
            p = pB;
        else           
            p = pG;
        
        for (j=i; j<i+aux1; j+=2) {
            ranD = gsl_rng_uniform(r);
            if (ranD<p) {
                v1 = j/2;
                v2 = (v1 + L)%N;
                
                add_link(v1, v2);
            }
        }
    }
}
