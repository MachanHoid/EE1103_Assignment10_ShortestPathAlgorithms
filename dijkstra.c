#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//this file is to implement djikstra's algorithm
double** define2darray(int n){
  double **array;
  array = malloc (sizeof (double *) * n);
  for (int i = 0; i < n; i++){
    array[i] = malloc (sizeof (double) * n);
  }
  return array;
}

int min_index(int n, double * array){
    int mini = 0;
    for(int i = 1; i<n; i++){
        if (array[i] < array[mini]){
            mini = i;
        }
    }
    return mini;
}

int in_intArray(int n, int k, int* array){
    int flag = 0;
    for(int i = 0; i<n; i++){
        if(array[i] == k){
            flag = 1;
            break;
        }
    }
    return flag;
}

//note: we are numbering nodes from 0 to n-1. same will be followed in cost matrix as well.
void dijsktra_compute(int n, double **cost, int sourcenode, int* visited, double *distance, int* via){
    //initialisation
    for(int i = 0; i <n; i++){
        distance[i] = INFINITY;
    }
    //first step
    distance[sourcenode] = 0;
    

    //iterations
    for(int j = 0; j<n; j++){
        int k = min_index(n, &distance);
        visited[j] = k;
        for(int i = 0; i < n; i++){
            if(in_intArray(n, i, &visited) == 0){
                if(distance[k] + cost[k][i] < distance[i]){
                    distance[i] = distance[k] + cost[k][i];
                    via[i] = k;
                }
            }
        }
    }
}

void dijkstra_display(int n, int sourcenode, double *distance, int* via){
    for(int i = 0; i<n; i++){
        printf("Shortest distance to node %d is: %lf\n", i, distance[i]);
        printf("The shortest path is:\n");
        printf("%d ",i );
        int p = i;
        while(p != sourcenode){
            p = via[p];
            printf("<-- %d ", p);
        }
        printf("\n\n");
    }
}

void dijkstra(int n, double **cost, int sourcenode){
    int* visited = malloc(sizeof(int) * n);
    double* distance = malloc(sizeof (double) * n);
    int* via = malloc(sizeof(int) * n);
    dijsktra_compute(n, cost, sourcenode, visited, distance, via);
    dijkstra_display(n, sourcenode, distance, via);
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
    dijkstra(n, cost, 0);
}