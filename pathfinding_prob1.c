#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//We use this function to define a nxn matrix
double** define2darray(int n){
  double **array;
  array = malloc (sizeof (double *) * n);
  for (int i = 0; i < n; i++){
    array[i] = malloc (sizeof (double) * n);
  }
  return array;
}

//to display a 1d array of doubles
void display1darray_double(int n, double* array){
    for(int i = 0; i<n; i++){
        printf(" %lf |", array[i]);
    }
}

//to display a 1d array of ints
void display1darray_int(int n, int* array){
    for(int i = 0; i<n; i++){
        printf(" %d,", array[i]);
    }
}

//membership operator for an array of ints
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

//returns the index of the minimum value in distance array which is not in visited array
int next_min_index(int n, double * array, int* visited){
    int minindex;
    double minivalue = INFINITY;
    //iterating through all the distances
    for(int i = 0; i<n; i++){
        //checking if node is not in visited array and if it has minimum value
        if ( (in_intArray(n, i, visited) == 0) && (array[i] < minivalue)){
            //updating index of minimum value
            minindex = i;
            //updating the minimum value
            minivalue = array[i];
        }
    }
    //if all the values that are not visited are infinity, then we return the next unvisited index
    if(minivalue == INFINITY){
        for(int i = 0; i<n; i++){
            if (in_intArray(n, i, visited) == 0){
            minindex = i;
            }
        }
    }
    //returning the minimum index
    return minindex;
}

//note: we are numbering nodes from 0 to n-1. same will be followed in cost matrix as well.
void dijsktra_compute(int n, double **cost, int sourcenode, int* visited, double *distance, int* via, int print_steps){
    //initialisation
    for(int i = 0; i <n; i++){
        visited[i] = -1;
        distance[i] = INFINITY;
        via[i] = -1;
    }
    //first step - setting distance of source node to be 0
    distance[sourcenode] = 0;

    //printing out the step by step operation for debugging and understanding
    if(print_steps ==1){
        printf("i |     Visited Array       |                      Distances                     \n");
        printf("%d |", 0);
        display1darray_int(n, visited);
        printf(" |");
        display1darray_double(n, distance);
        printf("\n");
    }
    //iterations
    for(int j = 0; j<n; j++){
        //finding the next index with minimum distance
        int k = next_min_index(n, distance, visited); 
        //adding this index to the visited array
        visited[j] = k;
        //iterating through all nodes
        for(int i = 0; i < n; i++){
            //checking for nodes that are not yet visited
            if(in_intArray(n, i, visited) == 0){
                //checking if the distance from this node is better than current distance
                if(distance[k] + cost[k][i] < distance[i]){
                    //updating new distance through this node
                    distance[i] = distance[k] + cost[k][i];
                    //updating the predecessor to keep track of the path
                    via[i] = k;
                }
            }
        }
        //printing out the visited and distance array for debugging and understanding step by step process
        if(print_steps ==1){
            printf("%d |", j+1);
            display1darray_int(n, visited);
            printf(" |");
            display1darray_double(n, distance);
            printf("\n");
    }
    }
}

//to display the results
void dijkstra_display(int n, int sourcenode, double *distance, int* via){
    //iterates through all nodes
    for(int i = 0; i<n; i++){
        //prints shortest distance
        printf("Shortest distance to node %d is: %lf\n", i, distance[i]);
        //prints shortest path by retracing
        printf("The shortest path is:\n");
        printf("%d ",i );
        int p = i;
        //stop condition is when p is the sourcenode
        while(p != sourcenode){
            //we update the index p to be its predecessor
            p = via[p];
            //if no path is available then no predecessor will be there so we print no path available
            if(p<0){
                printf("<-- No path is available.");
                break;
            }else{
                //we print the updated index
                printf("<-- %d ", p);
            }
        }
        printf("\n\n");
    }
}

//integrates both compute and display together
void dijkstra(int n, double **cost, int sourcenode, int print_steps){
    //initialising arrays to be passed
    int* visited = malloc(sizeof(int) * n);
    double* distance = malloc(sizeof (double) * n);
    int* via = malloc(sizeof(int) * n);

    //calling compute and then display.
    dijsktra_compute(n, cost, sourcenode, visited, distance, via, print_steps);
    dijkstra_display(n, sourcenode, distance, via);
}

//note: we are numbering nodes from 0 to n-1. same will be followed in cost matrix as well.
void bellmanford_compute(int n, double **cost, int sourcenode, double *distance, int* via, int print_steps){
    //initialisation
    for(int i = 0; i <n; i++){
        distance[i] = INFINITY;
        via[i] = -1;
    }
    //first step - setting distance of source node to be 0
    distance[sourcenode] = 0;

    //printing out the step by step operation for debugging and understanding
    if(print_steps ==1){
        printf("i |                      Distances                     \n");
        printf("%d |", 0);
        display1darray_double(n, distance);
        printf("\n");
    }
    //|V| - 1 iterations
    for(int a = 0; a<n-1; a++){
        //iterating through each edge
        for(int j = 0; j<n; j++){
            for(int i = 0; i < n; i++){
                //checking for a valid edge (i != j)
                if(i != j){
                    //checking if distance through this edge is better than current distance
                    if(distance[j] + cost[j][i] < distance[i]){
                        //updating new distance
                        distance[i] = distance[j] + cost[j][i];
                        //updating predecessor index
                        via[i] = j;
                    }
                }
            }
        }
        //printing out the step by step operation for debugging and understanding
        if(print_steps ==1){
            printf("%d |", a+1);
            display1darray_double(n, distance);
            printf("\n");
        }
    }

}

//to display the results
void bellmanford_display(int n, int sourcenode, double *distance, int* via){
    //iterating through all the nodes
    for(int i = 0; i<n; i++){
        //printing the shortest distance from distance array
        printf("Shortest distance to node %d is: %lf\n", i, distance[i]);
        //prints shortest path by retracing
        printf("The shortest path is:\n");
        printf("%d ",i );
        int p = i;
        //stop condition is when p is the sourcenode
        while(p != sourcenode){
            //we update the index p to be its predecessor
            p = via[p];
            //if no path is available then no predecessor will be there so we print no path available
            if(p<0){
                printf("<-- No path is available.");
                break;
            }else{
                //we print the updated index
                printf("<-- %d ", p);
            }
        }
        printf("\n\n");
    }
}

//to integrate both compute and display functions
void bellmanford(int n, double **cost, int sourcenode, int print_steps){
    //initialising arrays to be passed to functions
    int* visited = malloc(sizeof(int) * n);
    double* distance = malloc(sizeof (double) * n);
    int* via = malloc(sizeof(int) * n);

    //calling compute and display functions
    bellmanford_compute(n, cost, sourcenode, distance, via, print_steps);
    bellmanford_display(n, sourcenode, distance, via);
}

void main(){
    //initialising problem statement
    int n = 6;
    double** cost = define2darray(n);
    double cost_given[6][6] = {{0.0, 3.0, INFINITY, 1.0, INFINITY, INFINITY},
                               {3.0, 0.0, 1.1, 6.0, 15.0, 2.0},
                               {INFINITY, 3.0, 0.0, INFINITY, INFINITY, 9.0},
                               {1.0, 6.0, INFINITY, 0.0, 12.0, INFINITY},
                               {INFINITY,15.0, INFINITY, 12.0, 0.0, 6.0},
                               {INFINITY, 2.0, 9.0, INFINITY, 6.0, 0.0}};
    
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cost[i][j] = cost_given[i][j];
        }
    }
    //calling functions for required source nodes and printing the results.
    printf("\nUsing Dijkstra Algorithm:\n\n");
    dijkstra(n, cost, 0, 1);

    printf("\nUsing Bellman-Ford Algorithm:\n\n");
    bellmanford(n, cost, 0, 1);
}