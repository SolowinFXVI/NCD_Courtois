#include <stdio.h>
#include <stdlib.h>
#include "../include/structures.h"

/*
* Initialisation de la matrice avec des valeurs à -1
*/
void init_initial_matrix(node_t * P[],int matrix_size){
    for (int i = 0; i < matrix_size; i++)
    {
        node_t * init_node = (node_t *) malloc(sizeof(node_t));
        init_node->column = i;
        init_node->row = -1;
        init_node->val = -1;
        init_node->next = NULL;
        P[i] = init_node;
    }
}

/*
* Insert des valeurs a la fin de la liste chainée d'une ligne
*/
void insert_fin(node_t * P[], double val, int column, int row){
    node_t * current = P[column];
    if((current->next == NULL) && (current->val== -1.0) && (current->row==-1)){
        current->column = column;
        current->row = row;
        current->val = val;
    }
    else
    {
        node_t * newNode = (node_t *) malloc(sizeof(node_t));
        newNode->column = column;
        newNode->row = row;
        newNode->val = val;
        newNode->next = NULL;
        while (current->next != NULL)
        {
            current=current->next;
        }
        current->next = newNode;
    }
}

void insert_values(node_t * P[], int matrix_size){
    /*PLACE HOLDER FOR TESTING*/ /*Matrice 10*10*/
    insert_fin(P,0.5,2,0);
    insert_fin(P,0.5,8,0);

    insert_fin(P,0.25,0,1);
    insert_fin(P,0.25,3,1);
    insert_fin(P,0.25,8,1);
    insert_fin(P,0.25,9,1);

    insert_fin(P,0.25,0,2);
    insert_fin(P,0.25,3,2);
    insert_fin(P,0.25,4,2);
    insert_fin(P,0.25,6,2);

    insert_fin(P,0.5,0,3);
    insert_fin(P,0.5,4,3);

    insert_fin(P,0.5,1,4);
    insert_fin(P,0.5,9,4);
    
    insert_fin(P,0.5,2,5);
    insert_fin(P,0.5,6,5);
    
    insert_fin(P,0.5,7,6);
    insert_fin(P,0.5,8,6);
    
    insert_fin(P,1,1,7);

    insert_fin(P,1,9,8);

    insert_fin(P,1,6,9);

}


/*
* Affiche la Matrice creuse
*/
void print_matrix(node_t * P[], int matrix_size){
    printf("\n######### M A T R I X ###########\n");
    for (int i = 0; i < matrix_size; i++)
    {
        node_t * current = P[i];
        while(current != NULL){
            printf("||col:%d|row:%d|val:%lf||->",current->column ,current->row ,current->val);
            current=current->next;
        }
        printf("\n");
    }
    printf("#################################\n");
}

int get_matrix_size(){
    return 10;
}

void free_matrix(node_t * P[], int matrix_size){
    node_t * tmp;
    for (int i = 0; i < matrix_size; i++)
    {
        while(P[i] != NULL){
            tmp = P[i];
            P[i] = P[i]->next;
            free(tmp);
        }
    }
    
}

int main(int argc, char const *argv[])
{
    int matrix_size = get_matrix_size();
    node_t * P[matrix_size];
    init_initial_matrix(P,matrix_size);
    insert_values(P,matrix_size);
    print_matrix(P,matrix_size);
    free_matrix(P, matrix_size);
    printf("FIN");
    return 0;
}