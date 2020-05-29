#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "../include/structures.h"

int DEBUG = 1; //displays matrix
int DEBUG_2 = 0; //advanced debug
int DEBUG_FREES = 0;
int DEBUG_READ = 0;

double SEUIL = 0.000001; //seuil pour la convergence
static int nodeCount = 0;
static int totalNodes = 0;
static int shown = 0; //pour affichage du chargement du fichier

/*
* Affiche les éléments de la liste chainée d'une matrice
*/
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

/*
* Insert une valeur en deuxième position, juste après la node qui forme le tableau,
* sauf si il n'y a pas de node dans le tableau, 
* dans ce cas c'est inséré directement dans le tableau.
* Affiche le chargement du fichier.
*/
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

    //Affichage chargement du fichier
    nodeCount++;
    {
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
}

/*
 * Récupère la taille de la matrice principale depuis le fichier. 
*/
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

/*
* Récupère le nombre total de nodes depuis le fichier.
*/
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

/*
* Initialise la matrice principale en lisant depuis le fichier.
*/
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

/*
* Affiche la matrice principale, l'affichage montre les colonnes en abscisses.
*/
void print_matrix(int matrix_x_size, int y, node_t P[]){
    printf("\n############## MATRIX ###############\n");
    for (int x = 0; x < matrix_x_size; x++)
    {
        print_list(&P[x]);
        printf("\n");
    }
    printf("############## EOF MATRIX ###############\n");
}

/*
* Réstitue la mémoire allouée pour les nodes de la matrice.
*/
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

/*
* Met les valeurs du tableau de la matrice à 0.
*/
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

/*
* Allocation de la matrice.
*/
node_t * alloc_Matrix(int matrix_size){
    return malloc(matrix_size * sizeof(node_t));
}

/*
int couplage( node_t * P[], int matrix_size){
	int somme = 0; // variable permettant de stocker la somme des calculs pour m et k
	node_t * A = alloc_Matrix(matrix_size); 
	
		
	for (int j = 0; j < matrix_x_size; j++) //parcour des colonnes de la matrice A
    {
		p[j] = matrice_diagonal[i,j];	//reccuperation du bloc digonal correspondant a i,j
		if(P[j].next != NULL){ //Si la colonne de P[i,j] possède 2 ou plus valeur de ligne à traiter
			node_t * tmp = P[j].next;
			/// pour si la colonne j possède deux ligne i ayant une valeur 
			while(tmp->next != NULL){  
				for (int k = 0; k < matrix_x_size; k++) //parcour des colonnes de la matrice P[M,K]
				{
					if(P[k].next != NULL){ // si la colonne possède deux lignes apour lesqelles il y a une valeur
						node_t * current = P[k].next; 
						while(current->next != NULL){ //tant que la colonne possède plus de deux valeurs
							
							somme = somme + P[k]* Pi; // on rajoute à la variable "somme" le produit entre Pi,j [m, k] et πi[m]
							P[k].next = next; //on passe à l'élement suivant de la colone
						}
						somme = somme +P[k].next*pi; //ajoute quand il n'y a que deux valeurs
					}
						 
					else { //si la colonne k ne possède qu'une ligne M ayant une valeur
						somme = somme + P[k]* Pi; //Si la colonne ne contient qu'une valeur, on l'ajoute à "somme"
						A[j] = somme;
						A[j].next = next;
						P[j].next = next; //on passe a la valeur de la ligne suivante
					}
				}		 
			}
			/// pour si la colonne j ne possède que deux lignes i ayant des valeurs
			for (int k = 0; k < matrix_x_size; k++) //parcour des colonnes de la matrice P[M,K]
			{
				if(P[k].next != NULL){ // si la colonne possède deux lignes apour lesqelles il y a une valeur
					node_t * current = P[k].next; 
					while(current->next != NULL){ //tant que la colonne possède plus de deux valeurs
						
						somme = somme + P[k]* Pi; // on rajoute à la variable "somme" le produit entre Pi,j [m, k] et πi[m]
						P[k].next = next; //on passe à l'élement suivant de la colone
					}
					somme = somme +P[k].next*pi; //ajoute quand il n'y a que deux valeurs
				}	 
				else { //si la colonne k ne possède qu'une ligne M ayant une valeur
					somme = somme + P[k]* Pi; //Si la colonne ne contient qu'une valeur, on l'ajoute à "somme"
					A[j] = somme;
					A[j].next = next;
					P[j].next = next; //on passe a la valeur de la ligne suivante
				}
			}
			}
		///pour si la colonne j ne possède qu'une ligne i ayant une valeur
		else{ //si la colonne j ne contient qu'une seule ligne i possédant une valeur à traiter
			for (int k = 0; k < matrix_x_size; k++) //parcour des colonnes de la matrice P[M,K]
			{
				if(P[k].next != NULL){ // si la colonne possède deux lignes apour lesqelles il y a une valeur
					node_t * current = P[k].next; 
					while(current->next != NULL){ //tant que la colonne possède plus de deux valeurs
						
						somme = somme + P[k]* Pi; // on rajoute à la variable "somme" le produit entre Pi,j [m, k] et πi[m]
						P[k].next = next; //on passe à l'élement suivant de la colone
					}
					somme = somme +P[k].next*pi; //ajoute quand il n'y a que deux valeurs
				}	 
				else { //si la colonne k ne possède qu'une ligne M ayant une valeur
					somme = somme + P[k]* Pi; //Si la colonne ne contient qu'une valeur, on l'ajoute à "somme"
					A[j] = somme;
					A[j].next = next;
					P[j].next = next; //on passe a la valeur de la ligne suivante
				}
			}			
			
			
		}
	}
	return A[j];
}
*/

/*
* Allocation du tableau de matrices des blocks diagonaux.
*/
node_t ** alloca_blocksDiagonaux(int nbrBlocks, int sizeBlocks[]){
    int total = 0;
    for(int i = 0; i < nbrBlocks; i++){
        total += sizeBlocks[i];
    }
    printf("Total = %d \n", total);
    return malloc(sizeof(node_t) * total);
}

/*
* Initialisation basique de PI avec 1/taille.
*/
void init_PI(double PI[], int size){
    for(int i = 0; i < size; size++){
        PI[i] = (1/size);
    }
}

/*
* Comparaison entre deux tours de l'algorithme puissance.
*/
int compare_prev(int matrix_size, double PREV_G[], double G[]){
    for (int i = 0; i < matrix_size; i++)
    {
        if(fabs(G[i]-PREV_G[i]) > SEUIL){
            return 1;
        }
    }
    return 0;
}

/*
* Partie multiplicative de l'algorithme de puissance.
*/
void compute(int size, node_t block[], double PI[]){
    double res = 0.0;
    double res_prec = 0.0;
    double * TMP = malloc(sizeof(double) * size);
    for(int k = 0; k < size; k++){
        TMP[k] = 0.0;
    }
    for(int i = 0; i < size; i++){
        node_t current = block[i];
        while(current.next != NULL){
            res_prec = res;
            res = res + (current.val * PI[current.row]);
            current.column = current.next->column;
            current.row = current.next->row;
            current.val = current.next->val;
            current.next = current.next->next;
        }
        res_prec = res;
        res = res + (current.val * PI[current.row]);
        TMP[i] = res;
        res = 0.0;
        current.column = -1;
        current.row = -1;
        current.val = -1;
        current.next = NULL;
    }
    for(int j = 0; j < size; j++){
        PI[j] = TMP[j];
    }
    free(TMP);
}


/*
* Normalisation d'un vecteur. Ici PI.
*/
void normalize(int size,double PI[]){
    double sum = 0.0;
    double leftover = 0.0;
    int countNonZero = 0;
    for(int i = 0; i < size ; i++){
        sum += PI[i];
        if(PI[i] != 0.0){
            countNonZero++;
        }
    }
    leftover = 1-sum;
    leftover = leftover / countNonZero; //fraction de normalisation
    for(int i = 0; i < size; i++){
        if(PI[i] != 0.0){
            PI[i] += leftover;
        }
    }
}


/*
* Implémentation de l'algorithme de puissance, avec normalisation. //Question 1
*/
void puissance_et_normalisation(double ** vecteurs_propres, node_t ** blocksDiagonaux, int nbr_blocks, int sizeBlock[]){
    for(int i = 0; i < nbr_blocks; i++){
        int ite = 0;
        double * PI = malloc(sizeof(double) * sizeBlock[i]);
        init_PI(PI, sizeBlock[i]);
        double * PREV_PI = malloc(sizeof(double) * sizeBlock[i]);
        
        do{ 
            for(int j = 0; j < sizeBlock[i]; j++){
                PREV_PI[j] = PI[j];
            }
            normalize(sizeBlock[i],PI);
            compute(sizeBlock[i], blocksDiagonaux[i], PI);
            ite++;
        }while(((compare_prev(sizeBlock[i], PREV_PI, PI)) == 1) && (ite < 10000));
        for(int k = 0; k < sizeBlock[i]; k++){
            vecteurs_propres[i][k] = PI[k];
        }
        free(PI);
        free(PREV_PI);
    }
}


/*
* Initialisation des blocks diagonaux.
* /!\ Ici il nous manque des données cruciales/!\
*/
void init_blocksDiagonaux(int nbr_Blocks, int sizeBlock[], node_t ** blockDiagonaux){//TODO

}

/*
* Allocation mémoire pour les vecteurs propres.
*/
double ** alloca_vecteurs_propres(int nbrBlocks, int sizeBlocks[]){
    int total = 0;
    for(int i = 0; i < nbrBlocks; i++){
        total += sizeBlocks[i];
    }
    printf("Total = %d \n", total);
    return malloc(sizeof(double) * total);
}

/*
* Initialisation des vecteurs propres.
*/
void init_vecteurs_propres(int nbr_blocks,int sizeBlock[], double ** vecteurs_propres){
    for(int i = 0; i < nbr_blocks; i++){
        for(int j = 0; j < sizeBlock[i]; j++){
            vecteurs_propres[i][j] = 0;
        }
    }
}

/*
* Méthode des puissance sur la matrice de couplage. //QUESTION 3
*/
void puissance_sur_matrice_de_couplage(node_t A[], int sizeA, double PI[]){
    int ite = 0;
        init_PI(PI, sizeA);
        double * PREV_PI = malloc(sizeof(double) * sizeA);
        
        do{ 
            for(int j = 0; j < sizeA; j++){
                PREV_PI[j] = PI[j];
            }
            compute(sizeA, A, PI);
            ite++;
        }while(((compare_prev(sizeA, PREV_PI, PI)) == 1) && (ite < 10000));
        if(ite % 250 == 0){
            printf("Puissance sur matrice couplage = %d iteration \n", ite);
        }
        free(PREV_PI);
}

/*
* Calcul du PI final. Résultat de l'algorithme //QUESTION 4
*/
void final_PI(double ** vecteurs_propres, double PI[],int sizeBlocks[], int sizeA){
    double res = 0.0;
    for(int i = 0; i < sizeA; i++){
        for(int j = 0; j < sizeBlocks[i]; j++){
            res = res + (vecteurs_propres[i][j] * PI[i]);
        }
        PI[i] = res;
        res = 0.0;
    }
}

/*
* Affichage du vecteur PI.
*/
void print_PI(int sizeA, double PI[]){
    printf("\n ######## PI #########");
    for(int i = 0; i < sizeA; i++){
        printf("%lf ", PI[i]);
    }
    printf("\n ######## EOF PI #########");
}

/*
* Fonction principale, ou sont regroupées les allocation et executions.
* Le main mesure le temps d'execution de cette fonction.
* Dans cette fonction le temps de la partie calculatoire est également mesuré pour comparaison avec Pagerank.
*/
void run(char * path){
    struct timeval tv3, tv4;

    /*Inititalisation des la matrice principale*/
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
    
    /*Initialisation des Blocks diagonaux et vecteurs propres*/
    int nbr_blocks = 10;
    int sizeBlock[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //TODO
    int sizeA = 10; //TODO taille matrice couplage
    node_t * A = alloc_Matrix(sizeA);
    node_t ** blocksDiagonaux = alloca_blocksDiagonaux(nbr_blocks, sizeBlock);
    init_blocksDiagonaux(nbr_blocks, sizeBlock, blocksDiagonaux);
    recup_blocs_diagonaux(P, P, matrix_size);
    double ** vecteurs_propres = alloca_vecteurs_propres(nbr_blocks, sizeBlock);
    init_vecteurs_propres(nbr_blocks, sizeBlock, vecteurs_propres);
    double * PI = malloc(sizeof(double) * sizeA);
    
    /*Partie calculatoire chronometrée*/
    gettimeofday(&tv3, NULL); //Début du chronomètre
    puissance_et_normalisation(vecteurs_propres, blocksDiagonaux, nbr_blocks, sizeBlock); //Q1, un vecteur propre par block diagonal, après convergence.
    puissance_sur_matrice_de_couplage(A, sizeA, PI); //Q3
    final_PI(vecteurs_propres, PI, sizeBlock, sizeA);//Q4
    /*calculs*/
    gettimeofday(&tv4, NULL); //Fin du chronomètre
    print_PI(sizeA, PI);
    printf("Compute time = %f seconds \n", (double) (tv4.tv_usec - tv3.tv_usec)/ 1000000 + (double) (tv4.tv_sec - tv3.tv_sec));
    
    /*NETTOYAGE*/
    free_matrix(P, matrix_size);
    free(P);
    free(PI);
}


int main(int argc, char const *argv[])
{
    printf("STARTING \n");
    //char * path = "./res/GraphesWebTest/web1.txt";
    char * path = "./res/matriceTest.txt";

    // Choix du fichier à lire
    //char * path = "./res/GraphesWebTest/web1.txt";
    //char * path = "./res/Stanford.txt/Stanford.txt";
    //char * path = "./res/wb_cs_stanford.txt/wb-cs-stanford.txt";
    struct timeval tv1, tv2;
    
    gettimeofday(&tv1, NULL); //début du chronomètre
    run(path);
    gettimeofday(&tv2, NULL); //fin du chronomètre
    
    printf("Execution time = %f seconds \n", (double) (tv2.tv_usec - tv1.tv_usec)/ 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    printf("FIN\n");
    exit(0);
}
