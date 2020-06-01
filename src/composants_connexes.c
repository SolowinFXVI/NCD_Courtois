#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 11

int stack[MAX_SIZE], top;

/*
*   @author hansaniperera : https://github.com/hansaniperera/Kosaraju-Algorithm/blob/master/SCC/main.c
*/


// A structure to represent an adjacency list node
struct adj_list_node
{
    int dest;
    int weight;
    struct adj_list_node *next;
};

// A structure to represent an adjacency list
struct adj_list
{
    struct adj_list_node *head;
};

// A structure to represent a graph
struct Graph
{
    int V;
    int *visited;
    struct adj_list *array;
};

//****************START OF METHODS RELATED TO GRAPH******************
//*******************************************************************
//*******************************************************************

// Function to create a new adjacency list node
struct adj_list_node *new_adj_list_node(int dest, int weight)
{
    struct adj_list_node *newNode = (struct adj_list_node *)malloc(sizeof(struct adj_list_node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to creates a graph with V vertices
struct Graph *create_graph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct adj_list *)malloc(V * sizeof(struct adj_list));

    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Fuction to add edges to transpose graph
void get_transpose(struct Graph *gr, int src, int dest, int weight)
{
    struct adj_list_node *newNode = new_adj_list_node(src, weight);
    newNode->next = gr->array[dest].head;
    gr->array[dest].head = newNode;
}

// Fuction to add edges to graph
void add_edge(struct Graph *graph, struct Graph *gr, int src, int dest, int weight)
{

    struct adj_list_node *newNode = new_adj_list_node(dest, weight);

    newNode->next = graph->array[src].head;

    graph->array[src].head = newNode;
    // ACTUALISE/CREE LE GRAPHE TRANSPOSE
    get_transpose(gr, src, dest, weight);
}

// Function to print the graph
void print_graph(struct Graph *graph1)
{
    int v;
    for (v = 0; v < graph1->V; ++v)
    {
        struct adj_list_node *temp = graph1->array[v].head;
        while (temp)
        {
            printf("(%d -> %d(%d))\t", v, temp->dest, temp->weight);
            temp = temp->next;
        }
    }
}

//***************START OF STACK FUNCTIONS**********************
//*************************************************************
//*************************************************************

// Function to push item to stack
void push(int x)
{
    if (top >= MAX_SIZE - 1)
    {
        printf("\n\tSTACK is over flow");
    }
    else
    {
        top++;
        stack[top] = x;
    }
}

// Function to pop item to stack
void pop()
{
    if (top <= -1)
    {
        printf("\n\t Stack is under flow");
    }
    else
    {
        top--;
    }
}

//*****************END OF STACK FUNCTIONS**********************
//*************************************************************
//*************************************************************


// Fuction to fill the stack
void set_fill_order(struct Graph *graph, int v, bool visited[], int *stack)
{

    visited[v] = true;

    int i = 0;

    struct adj_list_node *temp = graph->array[v].head;
    while (temp)
    {
        if (!visited[temp->dest])
        {
            set_fill_order(graph, temp->dest, visited, stack);
        }

        temp = temp->next;
    }

    push(v);
}

// A recursive function to print DFS starting from v
void dfs_recursive(struct Graph *gr, int v, bool visited[])
{
    visited[v] = true;
    printf("%d ", v);
    struct adj_list_node *temp = gr->array[v].head;

    while (temp)
    {
        if (!visited[temp->dest])
        {
            dfs_recursive(gr, temp->dest, visited);
        }
        temp = temp->next;
    }
}



//*****************END OF METHODS RELATED TO GRAPH*******************
//*******************************************************************
//*******************************************************************

//**************START OF STRONGLY CONNECTED COMPONENTS CHECK***************
//*************************************************************************
//*************************************************************************

void strongly_connected_components(struct Graph *graph, struct Graph *gr, int V)
{
    bool visited[V];
    for (int i = 0; i < V; i++) visited[i] = false;

    for (int i = 0; i < V; i++)
    {
        if (visited[i] == false)
        {
            printf("ici %d", i);
            set_fill_order(graph, i, visited, stack);
        }
    }
    int count = 1;
    for (int i = 0; i < V; i++){
        visited[i] = false;
    }

    while (top != -1)
    {
        int v = stack[top];
        pop();

        if (visited[v] == false)
        {
            printf("Sommet %d\n", v);
            printf("\nBloc diagonal %d: [", count++);
            dfs_recursive(gr, v, visited);
            printf("]\n");
        }
    }
}

//****************END OF STRONGLY CONNECTED COMPONENTS CHECK***************
//*************************************************************************
//*************************************************************************

//**************RECUPERATION MATRICE***************
//*************************************************************************
//*************************************************************************
int DEBUG = 1; //displays matrix
int DEBUG_2 = 0; //advanced debug
int DEBUG_FREES = 0;
int DEBUG_READ = 0;
void init_matrix(int matrix_size,char * path){
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

    int v = 11;

    struct Graph *graph = create_graph(v);
    struct Graph *gr = create_graph(v);

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
            //printf("sommet:%d,dest:%d \n", row, column);
            add_edge(graph, gr, row, column, val);        
        }
    }
    fclose(file);
    printf("GRAPHE:\n");
    print_graph(graph);
    printf("\nGRAPHE TRANSPOSE:\n");
    print_graph(gr);
    
    strongly_connected_components(graph, gr, matrix_size);
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


//************* FIN RECUP MATRICE***************
//*************************************************************************
//*************************************************************************

int main()
{
    top = -1;


    char * path = "../res/matriceTest.txt";
    int matrix_size = get_matrix_size(path);

    init_matrix(matrix_size, path);

    return 0;
}