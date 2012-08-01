//
//  percolation.h
//  Wolff-algorithm
//
//  Created by Marlon Ramos on 05/07/12.
//  Copyright (c) 2012 PUC-Rio. All rights reserved.
//

#ifndef Wolff_algorithm_percolation_h
#define Wolff_algorithm_percolation_h

void burning(void);
int bfs(int s);
void initBfs(void);
void endBfs(void);
void enqueue(int x);
int dequeue(void);
int init_queue(void);

#endif