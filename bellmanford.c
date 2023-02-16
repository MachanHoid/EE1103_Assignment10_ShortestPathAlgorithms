#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** define2darray(int n){
  double **array;
  array = malloc (sizeof (double *) * n);
  for (int i = 0; i < n; i++){
    array[i] = malloc (sizeof (double) * n);
  }
  return array;
}

void display1darray_double(int n, double* array){
    for(int i = 0; i<n; i++){
        printf(" %lf |", array[i]);
    }
}

void display1darray_int(int n, int* array){
    for(int i = 0; i<n; i++){
        printf(" %d,", array[i]);
    }
}

//note: we are numbering nodes from 0 to n-1. same will be followed in cost matrix as well.
void bellmanford_compute(int n, double **cost, int sourcenode, double *distance, int* via, int print_steps){
    //initialisation
    for(int i = 0; i <n; i++){
        distance[i] = INFINITY;
        via[i] = -1;
    }
    //first step
    distance[sourcenode] = 0;

    //printing out
    if(print_steps ==1){
        printf("i |                      Distances                     \n");
        printf("%d |", 0);
        display1darray_double(n, distance);
        printf("\n");
    }
    //iterations
    for(int a = 0; a<n-1; a++){
        for(int j = 0; j<n; j++){
            for(int i = 0; i < n; i++){
                if(i != j){
                    if(distance[j] + cost[j][i] < distance[i]){
                        distance[i] = distance[j] + cost[j][i];
                        via[i] = j;
                    }
                }
            }
        }
        if(print_steps ==1){
            printf("%d |", a+1);
            display1darray_double(n, distance);
            printf("\n");
        }
    }

}

void bellmanford_display(int n, int sourcenode, double *distance, int* via){
    for(int i = 0; i<n; i++){
        printf("Shortest distance to node %d is: %lf\n", i, distance[i]);
        printf("The shortest path is:\n");
        printf("%d ",i );
        int p = i;
        while(p != sourcenode){
            p = via[p];
            if(p<0){
                printf("<-- No path is available.");
                break;
            }else{
                printf("<-- %d ", p);
            }
        }
        printf("\n\n");
    }
}

void bellmanford(int n, double **cost, int sourcenode, int print_steps){
    int* visited = malloc(sizeof(int) * n);
    double* distance = malloc(sizeof (double) * n);
    int* via = malloc(sizeof(int) * n);

    bellmanford_compute(n, cost, sourcenode, distance, via, print_steps);
    bellmanford_display(n, sourcenode, distance, via);
}


void main(){
    int n = 6;
    double** cost = define2darray(n);
    double cost_given[6][6] = {{0.0, 1.5, INFINITY, INFINITY, INFINITY, 0.7},
                               {INFINITY, 0.0, 1.1, INFINITY, INFINITY, INFINITY},
                               {INFINITY, INFINITY, 0.0, INFINITY, 3.0, INFINITY},
                               {INFINITY, 2.3, 4.5, 0.0, INFINITY, INFINITY},
                               {INFINITY, INFINITY, INFINITY, INFINITY, 0.0, INFINITY},
                               {INFINITY, INFINITY, INFINITY, INFINITY, 6.5, 0.0}};
    
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cost[i][j] = cost_given[i][j];
        }
    }
    bellmanford(n, cost, 0, 1);
}