#ifndef STRUCTURES__H
#define STRUCTURES__H

//matrice creuse
/*
stocker les éléments non nuls
uniquement i,j P(i,j)
*/


typedef struct node_t{
    int column;
    int row;
    double val;
    struct node_t * next;
}node_t;






#endif