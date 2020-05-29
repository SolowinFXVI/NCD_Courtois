#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../include/structures.h"

int DEBUG = 1; //displays matrix
int DEBUG_2 = 0; //advanced debug
int DEBUG_FREES = 0;
int DEBUG_READ = 0;
static int nodeCount = 0;
static int totalNodes = 0;
static int shown = 0;


void print_list(node_t * head){
    node_t * current = head;
    while (current != NULL) {
        printf("||col:%d|row:%d|val:%lf||->",current->column,current->row,current->val);
        current=current->next;
    }
    printf("NULL");
}

//~ int vecteur_probabilité(node_t * P[], int matrix_size){
	
	//~ return v[..];
//~ }

//~ int bloc_diagonaux(node_t * P[], int matrix_size){
	
	//~ return P[i][j];
//~ }
//~ int couplage( node_t * P[], int matrix_size){
	//~ int somme = 0; // variable permettant de stocker la somme des calculs pour m et k
	//~ A[matrix_size] = init_initial_matrix(node_t * A[],int matrix_size)
	
	
	//~ for (int i = 0; i < matrix_size; i++) // parcours des lignes de la matrice A
    //~ {
        //~ for (int j = 0; j < matrix_size; j++) //parcours des colonnes de la matrice A
		//~ {
			//~ P[M][k] = bloc_diagonaux(i,j) // reccupere un bloc diagonal
				//~ for (int M = 0; M < matrix_size; M++) //parcours des lignes de la martice Pi,j[M][k]
				//~ {	
					//~ Pi[M] = vecteur_probabilite(i,M) // reccupere le vecteur de probabilite de i pour M
					//~ for (int k = 0; k < matrix_size; k++){ //parcours des colonnes de la martice Pi,j[M][k]
						//~ somme = somme + P[M][k] * Pi[M]; 
					//~ }
				//~ }
			//~ A[i][j] = somme;
		//~ }
	//~ }
//}

void insert_head(node_t P[], double val, int column, int row){
    if(P[column].next == NULL){
        if(P[column].row == -1){ //vide
            P[column].column= column;
            P[column].row=row;
            P[column].val = val;
            P[column].next = NULL;
        }
        else{ //pas de suivant
            node_t * newNode = malloc(sizeof(node_t));
            if(newNode == NULL){
            fprintf(stderr, "Unable to allocate memory for new node\n");
            exit(-1);
            }
            newNode->column = column;
            newNode->row = row;
            newNode->val = val;
            newNode->next = NULL;
            P[column].next = newNode;
        }
        
    }
    else{//suivants
        node_t * newNode = malloc(sizeof(node_t));
        if(newNode == NULL){
            fprintf(stderr, "Unable to allocate memory for new node\n");
            exit(-1);
        }
        newNode->column = column;
        newNode->row = row;
        newNode->val = val;
        newNode->next = P[column].next;
        P[column].next = newNode;
    }    
    nodeCount++;
        if(((nodeCount * 100)/totalNodes == 10) && (shown==0)){
        printf("Loading 10%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 20) && (shown==1)){
        printf("Loading 20%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 30) && (shown==2)){
        printf("Loading 30%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 40) && (shown==3)){
        printf("Loading 40%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 50) && (shown==4)){
        printf("Loading 50%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 60) && (shown==5)){
        printf("Loading 60%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 70) && (shown==6)){
        printf("Loading 70%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 80) && (shown==7)){
        printf("Loading 80%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 90) && (shown==8)){
        printf("Loading 90%% \n");
        shown++;
    }
    else if(((nodeCount * 100)/totalNodes == 99) && (shown==9)){
        printf("Loading 100%% \n");
        shown++;
    }
    if(DEBUG_2)printf("filled existing node : %d \n", nodeCount);
}

int get_matrix_size(char * path){
    int matrix_size = -1;
    int dummy = -1;
    FILE * file = fopen(path,"r");
    if(file==NULL){
        printf("could not open file \n");
        exit(-2);
    }
    fscanf(file,"%d",&matrix_size);
    fscanf(file,"%d",&dummy);
    fclose(file);
    return matrix_size;
}

int get_totalNodes(char * path){
    int dummy = -1;
    int nodes = -1;
    FILE * file = fopen(path,"r");
    if(file == NULL){
        printf("could not open file \n");
        exit(-2);
    }
    fscanf(file, "%d", &dummy);
    fscanf(file, "%d", &nodes);
    fclose(file);
    return nodes;
}

void init_matrix(int matrix_size,node_t P[],char * path){
    FILE *file = fopen(path,"r");
    if(file==NULL){
        if(DEBUG_2)printf("could not open file \n");
        exit(1);
    }
    int row = 0;
    int numberOfElements = 0;
    int dummmyMatrixSize = 0;
    int repsInALine = 0;
    int column = 0;
    double val = 0.0;

    fscanf(file, "%d", &numberOfElements);
    fscanf(file, "%d", &dummmyMatrixSize);

    for (int i = 0; i < matrix_size; i++)
    {
        fscanf(file, "%d", &row);
        fscanf(file, "%d", &repsInALine);
        if(DEBUG_READ)printf("row: %d, reps:%d \n", row-1, repsInALine);
        for (int j = 0; j < repsInALine; j++)
        {
            fscanf(file, "%d %lf", &column, &val);
            if(DEBUG_READ)printf("decider:col:%d,row:%d,val:%lf \n", column-1, row-1, val);
            insert_head(P,val, column-1, row-1);
            
        }
    }
    

    fclose(file);
}

void print_matrix(int matrix_x_size, int y, node_t P[]){
    printf("\n############## MATRIX ###############\n");
    for (int x = 0; x < matrix_x_size; x++)
    {
        print_list(&P[x]);
        printf("\n");
    }
    printf("############## EOF MATRIX ###############\n");
}

void free_matrix(node_t P[], int matrix_size) {
    
    for (int i = matrix_size-1; i >= 0; i--) {
        if(DEBUG_FREES) printf("free column %d \n", i);
        while(P[i].next != NULL){
            if(DEBUG_FREES){
                printf("next = %p ", P[i].next);
                printf("next->val = %lf ", P[i].next->val);
            }    
            node_t * current = P[i].next;
            if(current->next != NULL){
                node_t * next = current->next;
                P[i].next = next;
                free(current);
                if(DEBUG_FREES)printf("freed \n");
            }
            else{
                P[i].next = NULL;
                free(current);
                if(DEBUG_FREES)printf("freed \n");
            }
        }
    }
}

void zero_matrix(node_t P[], int matrix_size){
    for (int i = 0; i < matrix_size; i++)
    {
        P[i].column=i;
        P[i].row=-1;
        P[i].val=-1;
        P[i].next=NULL;
    }
}

/*
* Rend la matrice NCD en enlevant les arcs de poids inferieur à seuil
*/
void transform_NCD(node_t P[], int matrix_size, double seuil){
    int count_removed_arc = 0;
    node_t * dummy = malloc(sizeof(node_t));
    dummy->column = -1;
    dummy->row = -1;
    dummy->val = -1;
    dummy->next = NULL;
    node_t * prec_current = dummy;
    node_t * current = dummy;
    node_t * next_current = dummy;     

    for (int i = 0; i < matrix_size; i++){  // POUR CHAQUE COLONNE DE LA MATRICE
        if(P[i].next == NULL){  // S'IL N'Y A QU'UNE SEULE NODE DANS CETTE COLONNE
            if(P[i].val < seuil){
                P[i].val = -1;
                P[i].row = -1;
                count_removed_arc += 1;
            }
        }
        else if(P[i].next->next == NULL){ // S'IL N'Y A QUE DEUX NODES DANS CETTE COLONNE
            printf("2||col:%d|row:%d|val:%lf||\n",P[i].column,P[i].row,P[i].val);
            if(P[i].val < seuil){
                if(P[i].next->val < seuil){ // SI LES VALEURS DE TOUTE LES NODES DE LA COLONNE SONT INFERIEURE AU SEUIL
                    node_t * poubelle = P[i].next;
                    P[i].val = -1;
                    P[i].row = -1;
                    P[i].next = NULL;
                    count_removed_arc += 1;
                    free(poubelle);
                }
                else{   // SI UNIQUEMENT LA PREMIERE EST INFERIEURE
                    node_t * poubelle = P[i].next;
                    
                    P[i].val = P[i].next->val;
                    P[i].column = P[i].next->column;
                    P[i].row = P[i].next->row;
                    P[i].next = NULL;
                    free(poubelle);
                }
                count_removed_arc += 1;
            }
            
            if((P[i].next != NULL) && (P[i].next->val < seuil)){    // SI UNIQUEMENT LA DEUXIEME EST INFERIEURE
                    node_t * poubelle = P[i].next;
                    P[i].next = NULL;
                    free(poubelle);
                    count_removed_arc += 1;
            }
        }
        else{   // S'IL Y A 3 NODES OU PLUS DANS CETTE COLONNE
        printf("CAS 3");
            while(current->row == -1){  // TANT QUE LA PREMIERE NODE EST INFERIEUR ET QU'ON N'A PAS INITIALISE LES VARIABLES
                if(P[i].val < seuil){   // SI LA PREMIERE NODE EST INFERIEURE -> ON REMPLACE PAR VAL PROCHAINE NODE ET ON SUPP CETTE PROCHAINE NODE
                    node_t * poubelle = P[i].next;
                    printf("3-SUPP||col:%d|row:%d|val:%lf||\n",P[i].column,P[i].row,P[i].val);

                    P[i].val = P[i].next->val;
                    P[i].column = P[i].next->column;
                    P[i].row = P[i].next->row;
                    P[i].next = poubelle->next;
                    
                    free(poubelle);
                }
                else{   // SI LA PREMIERE NODE N'EST PAS INFERIEURE -> INITIALISATION
                    current = dummy;
                    current->column = P[i].column;
                    current->row = P[i].row;
                    current->val = P[i].val;
                    if(P[i].next != NULL) current->next = P[i].next;
                    
                    prec_current = current;
                    current = current->next;
                    next_current = current->next;
                } 
            }
            
            if(current->next == NULL) printf("NEXT NULL - ||col:%d|row:%d|\n",current->column,current->row);
            while(current->next != NULL){
                printf("3||col:%d|row:%d|val:%lf||\n",current->column,current->row,current->val);
                current = current->next;

                prec_current = current;
                next_current = current->next;
            }
        }
    }
    printf("Nombre d'arcs enleves: %d\n", count_removed_arc);
}

/*
* modifie : sizeBlock, blockDiagoanaux, nbrBlocks
* Détermination des composants connexe de GE et récupération de ces blocs dans G
* On utilise un algo de coloration, la couleur de chaque sommet est stocké dans la valeur column de ce sommet
*  BLANC = 0, GRIS = 1, NOIR = 2
*/
void recup_blocs_diagonaux(node_t GE[], node_t G[], int matrix_size/*, int sizeBlock[], node_t ** blocksDiagonaux, int nbrBlocks*/){
    printf("--------------------------\n");
    // COLORIAGE DE TOUT LES SOMMETS EN BLANC/0
    for (int x = 0; x < matrix_size; x++){
        node_t * current = &GE[x];
        while (current != NULL) {
            current->column = 0;
            current=current->next;
        }
    }
    //int temps = 0;

}
    

void DFS(){

}

node_t * alloc_Matrix(int matrix_size){
    return malloc(matrix_size * sizeof(node_t));
}


void run(char * path){
    struct timeval tv3, tv4;
    int matrix_size = get_matrix_size(path);
    totalNodes = get_totalNodes(path);
    node_t * P = alloc_Matrix(matrix_size);
    if(P == NULL){
        printf("Allocation Error \n");
        exit(-1);
    }
    zero_matrix(P, matrix_size);
    init_matrix(matrix_size, P , path);
    if(DEBUG) print_matrix(matrix_size, matrix_size, P);
    

    gettimeofday(&tv3, NULL);
    /*calculs*/
    //transform_NCD(P, matrix_size, 0.26);
    //print_matrix(matrix_size, matrix_size, P);
    // node_t GE[], node_t G[], int matrix_size, int sizeBlock[], node_t ** blocksDiagonaux, int nbrBlocks
    recup_blocs_diagonaux(P, P, matrix_size);
    /*calculs*/
    gettimeofday(&tv4, NULL);
    printf("Compute time = %f seconds \n", (double) (tv4.tv_usec - tv3.tv_usec)/ 1000000 + (double) (tv4.tv_sec - tv3.tv_sec));
    free_matrix(P, matrix_size);
    free(P);
}


int main(int argc, char const *argv[])
{
    printf("STARTING \n");
    //char * path = "./res/GraphesWebTest/web1.txt";
    char * path = "./res/matriceTest.txt";
    //char * path = "./res/Stanford.txt/Stanford.txt";
    //char * path = "./res/wb_cs_stanford.txt/wb-cs-stanford.txt";
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    run(path);
    gettimeofday(&tv2, NULL);
    printf("Execution time = %f seconds \n", (double) (tv2.tv_usec - tv1.tv_usec)/ 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    printf("FIN\n");
    exit(0);
}
