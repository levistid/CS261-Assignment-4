/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name: Levi Stidham
 * Email: stidhaml@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

#define DATA_FILE "airports.dat"
#define START_NODE 0
#define MAX 10000000

struct node{
  int key;
  int cost;
  struct node* previous;
};

struct node_t{
  struct node* previous;
  struct node* next;
};

struct node* make_node(int key){
  struct node* new_node = malloc(sizeof(struct node));
  new_node->key = key;
  new_node->cost = MAX;
  new_node->previous = NULL;
  return new_node;
};


struct node_t* new_nodeT(struct node* node, struct node* previous){
  struct node_t* nm = malloc(sizeof(struct node_t));
  nm->previous = previous;
  nm->next = node;
  return nm;
};

// void print(struct node* node){
//   if(node->previous != NULL){
//     print(node->previous);
//     printf("->");
//   }
//   printf("%d", node->key);
// }

void print(struct node* node){
  struct node* current = node;
    if(current->previous != NULL){
      printf("->");
    }
    printf("%d", current->key);
    current = current->previous;
  
}


void dijkstra(int** graph, int num_of_nodes, int start_node){
  struct node** new_node = malloc(num_of_nodes * sizeof(struct node*));

  for(int i = 0; i < num_of_nodes; i++){
    new_node[i] = make_node(i);
  }
  struct pq* pq = pq_create();
  pq_insert(pq,new_nodeT(new_node[START_NODE], NULL),0);

  while(!pq_isempty(pq)){
    int t = pq_first_priority(pq);

    struct node_t* nt = pq_remove_first(pq);
    struct node* n = nt->next;

    if(t < n->cost){
      n->cost = t;
      n->previous = nt->next;

      for(int i = 0; i <num_of_nodes; i++){
        if(graph[n->key][i]){
          pq_insert(pq,new_nodeT(new_node[i],n), t + graph[n->key][i]);
        }
      }
    } 
    free(nt);
  }
  for(int i = 0; i < num_of_nodes; i++){
    print(new_node[i]);
    printf("%d\n",new_node[i]->cost);
  }
  pq_free(pq);
  for(int i = 0; i < num_of_nodes; i++){
    free(new_node[i]);
  }
  free(new_node);
}

int main(int argc, char const *argv[]) {
  /*
   * Write your code here to read the file `airports.dat` and to find the
   * least-cost paths from node 0 to all other nodes in the graph.  Make sure
   * to print out the least-cost paths you find at the end.
   */

  int num_nodes = 0;
  int num_edges = 0;
  int node_x = 0, node_y = 0;

FILE* file = fopen(DATA_FILE, "r");

fscanf(file, "%d", &num_nodes);
fscanf(file, "%d", &num_edges);

int** matrix = malloc(num_nodes * sizeof(int*));
for(int i = 0; i < num_nodes; i++){
  matrix[i]= calloc(num_nodes,sizeof(int));
}

for(int j = 0; j < num_edges; j++){
  fscanf(file, "%d", &node_y);
  fscanf(file, "%d", &node_x);
  fscanf(file, "%d", &matrix[node_y][node_x]);
}
fclose(file);

printf("\n\nMatrix\n\n");
for(int i = 0; i < num_nodes; i++){
  printf("[");
  for(int j = 0; j < num_nodes; j++){
    printf("%5d",matrix[i][j]);
    if(j < num_nodes -1){
      printf(",");
    }
  }
      printf("]\n");
}

printf("\n\n Path Summary\n\n");
dijkstra(matrix,num_nodes, START_NODE);

for(int i = 0; i < num_nodes; i++){
  free(matrix[i]);
}
free(matrix);
}