//
//  percolation.c
//  Wolff-algorithm
//
//  Created by Marlon Ramos on 05/07/12.
//  Copyright (c) 2012 PUC-Rio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <gsl/gsl_rng.h>

#include "percolation.h"
#include "network.h"

int **nbr, *spin_state;   //adjacency list, and the state from strips on the square lattice
int *Z;                     //Vector that keep the vertices degree
int N, L;                   //total number of vertex and linear dimension of network

int *Q;
int Q_tail, Q_head;
int *distance;

int init_queue();
void enqueue(int x);
int dequeue();
int bfs(int s);

gsl_rng *r; 
double ranD;

int bfs(int s)
{
    int u, v;
    int TC=0; //Cluster size
    
    distance[s]=1;
    init_queue();
    enqueue(s); TC++; 
    
    while(Q_tail!=Q_head){
        u=dequeue();
        for(v=0;v<Z[u];v++){  
            if(!distance[nbr[u][v]]){
                enqueue(nbr[u][v]); TC++;
                distance[nbr[u][v]]=1;
            }
        }  
    }
    
    return TC;
}

void initBfs(void)
{
    distance=(int *)calloc(N, sizeof(int));
    Q=(int *)calloc(N, sizeof(int));
}

void endBfs(void)
{
    free(distance);
    free(Q);
}

void enqueue(int x)
{
    Q[Q_tail]=x;
    Q_tail=(Q_tail+1)%(N-1);
}

int dequeue()
{
    int x=Q[Q_head];
    Q_head=(Q_head+1)%(N-1);
    return x;
}


int init_queue(void)
{
    Q_tail = Q_head = 0;
    return 0;
}