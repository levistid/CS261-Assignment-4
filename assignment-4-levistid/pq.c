/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Levi Stidham 
 * Email: stidhaml@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq
{
  struct dynarray* darr;
  
};
struct node{
    void* val;
    int size;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq *temp = malloc(sizeof(struct pq));
  temp->darr = dynarray_create();
  return temp;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  int i = 0;

  while(!pq_isempty(pq)){
    free(dynarray_get(pq->darr,i));
    i++;
  }

  dynarray_free(pq->darr);
  pq->darr = NULL;
  free(pq);
  pq = NULL;
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  
  if(dynarray_size(pq->darr) > 0){
    return 0;
  }
  return 1;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */

// void up_cap_pq(struct pq* pq){
//   int capacity = pq->capacity_pq;
//   pq->capacity_pq = pq->darr->capacity;
//   int* new_arr = malloc(pq->capacity_pq * sizeof(int));
//   for(int i = 0; i < capacity ; i++){
//     new_arr[i] = pq->priority[i];
//   }
//   free(pq->priority);
//   pq->priority = new_arr;
// }

// int parent_finder(int i){
//   return (i-1)/2;
// }

void swap(struct dynarray *arr, int index1, int index2){
  void *data = dynarray_get(arr,index1);
  dynarray_set(arr, index1, dynarray_get(arr, index2));
  dynarray_set(arr, index2, data);
}



void perc(struct pq* pb){
  int last = dynarray_size(pb->darr) -1;
  int parent_idx = (last - 1)/2;
  int parent = ((struct node*) dynarray_get(pb->darr,parent_idx))->size;
  int child = ((struct node*) dynarray_get(pb->darr,last))->size;

  while(parent > child){
    void* i = dynarray_get(pb->darr, parent_idx);
    void* t = dynarray_get(pb->darr, last);

    dynarray_set(pb->darr,last,i);
    dynarray_set(pb->darr,parent_idx, t);

    last = parent_idx;
    parent_idx = (last -1)/2;
    parent = ((struct node*) dynarray_get(pb->darr, parent_idx))->size;
    child = ((struct node*) dynarray_get(pb->darr,last)) ->size;
  }
}

void pq_insert(struct pq* pq, void* value, int priority) {
  struct node* temp = malloc(sizeof(struct node));
  temp->size = priority;
  temp->val = value;
  dynarray_insert(pq->darr, temp);
  perc(pq);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  if(pq_isempty(pq)){
    return NULL;
  }
  return((struct node*)dynarray_get(pq->darr, 0))->val;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  return ((struct node*)dynarray_get(pq->darr,0))->size;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

int find_low(struct pq* pq, int i){
  int left = (2* i) +1;
  int right = (2 * i) +2;
  int minimum = 0;
  if((left < dynarray_size(pq->darr)) && (right < dynarray_size(pq->darr))){

  } 
}


void prioritize(struct pq* pq){
  int i = 0;
  int minimum = find_low(pq, i);

  while (minimum >= 0 && ((((struct node*) dynarray_get(pq->darr,i))->size > ((struct node*)dynarray_get(pq->darr, minimum))->size))){
    int x = minimum;
    void* m = dynarray_get(pq->darr,i);
    void* n = dynarray_get(pq->darr, minimum);
    dynarray_set(pq->darr,minimum,m);
    dynarray_set(pq->darr,i,n);

    i = x;
    minimum = find_low(pq,i);

  }
}

int find_left(int i){
  return i * 2 +1;
}

int find_right(int i){
  return i * 2 + 2;
}

void perc_down(struct dynarray *arr, int index){
  if((2 * index)+1 >= dynarray_size(arr)){
    return;
  }

  int min_index = (2 * index) +1;
  struct node *min = (struct node*)dynarray_get(arr,min_index);

  if((2 * index)+2 < dynarray_size(arr)){
    if(min->size >((struct node*)dynarray_get(arr, (2* index)+2))->size){
      min_index = (2*index)+2;
      min = (struct node*)dynarray_get(arr,min_index);
    }
  }

  if(min->size < ((struct node*) dynarray_get(arr,index))->size){
    swap(arr, index, min_index);
    perc_down(arr, min_index);
  }
}


void* pq_remove_first(struct pq* pq){
  void* first = pq_first(pq);

  free(dynarray_get(pq->darr,0));

  dynarray_set(pq->darr,0,dynarray_get(pq->darr,dynarray_size(pq->darr)-1));

  dynarray_remove(pq->darr,dynarray_size(pq->darr)-1);

  perc_down(pq->darr,0);

  return first; 


}