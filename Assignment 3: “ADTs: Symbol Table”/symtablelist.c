#include "symtable.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
  const char *key;
  const void *value;
  struct Node *next;
}Node_t;

 typedef struct SymTable{
  Node_t *head;
}SymTable;

/*
 *Returns a new empty Symtable (with no bindings)
 */
 SymTable_T SymTable_new(void){

  SymTable_T newSymTable;
  newSymTable = (SymTable_T)malloc(sizeof(SymTable));

  if(newSymTable == NULL){
    return NULL;
  }
  newSymTable -> head = NULL;
  return newSymTable;
}
/*
 *Free all memory that oSymTable uses
 */
  void SymTable_free(SymTable_T oSymTable){
    Node_t *current;
    Node_t *nextNode;

    assert(oSymTable != NULL);
    current = oSymTable -> head;
    while (current != NULL) {
      nextNode = current -> next;
      free((char*)(current -> key));
      free(current);
      current = nextNode;
    }
    free(oSymTable);
  }
/*
 *Returns the number of bindings in symtable(length)
 */
unsigned int SymTable_getLength(SymTable_T oSymTable){
  Node_t *current = oSymTable -> head;
  unsigned int length = 0;

    while (current != NULL) {
      length++;
      current = current -> next;
    }
  return length;
}
/*
 *If there isnt any binding with the same key a new
 *binding will be added with key pcKey and value
 *pvValue. Return 1 if success else return 0
 */
 int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
   Node_t *newNode;
   const char *pcKeyCopy;

   assert(oSymTable != NULL);
   assert(pcKey != NULL);

   /*Allocate enough memory for a new Node*/
   newNode = (Node_t*)malloc(sizeof(Node_t));
   if(newNode == NULL){
     return 0;/*Not enough memory*/
   }
   /*Allocate enough memory for pcKeyCopy with \0*/
   pcKeyCopy = (char*)malloc(strlen(pcKey) * sizeof(char) + 1);
   if(pcKeyCopy == NULL){
     return 0;/*Not enough memory*/
   }

   /*check if binding with key pcKey already exists
     and free alocated memory of newNode and keyCopy*/
   if( SymTable_contains(oSymTable, pcKey) ){
     free(newNode);/*free memory of newNode*/
     free((char*)pcKeyCopy);/*free the alocated memory for keyCopy*/
     return 0;
   }

     /*Copy key to pcKeyCopy*/
     strcpy((char*)pcKeyCopy , (char*)pcKey);
     /*check if oSymTable is empty.If empty newNode
      is the first node of the list(head)*/
     if( SymTable_getLength(oSymTable) == 0){
       newNode -> key = pcKeyCopy;
       newNode -> value = pvValue;
       newNode -> next = NULL;
       oSymTable -> head = newNode;
       return 1;
     }

   /*Insert binding in the beginning of the list*/
   newNode -> key = pcKeyCopy;
   newNode -> value = pvValue;
   newNode -> next = oSymTable -> head;
   oSymTable -> head = newNode;
   return 1;
 }
/*
 *If there is a binding with key pcKey it will SymTable_remove
  *the binding and return 1(TRUE) else return(TRUE)
 */
int   SymTable_remove(SymTable_T oSymTable, const char *pcKey){
  Node_t *current;
  Node_t *prev;

  assert(oSymTable != NULL);
  assert(pcKey != NULL);
  current = oSymTable -> head;
    while(current != NULL){
      if( strcmp( current -> key, pcKey) == 0){
	       if(current == oSymTable -> head){
                  oSymTable -> head = current -> next;
                  free( (char*)(current -> key) );
                  free(current);
                  return 1;
                }else {
                  prev -> next = current -> next;
                  free( (char*)(current -> key) );
                  free(current);
                  return 1;
                }
	       }
         prev = current;
      current = current -> next;
    }/*End of while*/
 return 0; /*binding with key pcKey not found*/
}

 /*
  *Returns 1 if the Symtable contains the binding with pcKey
  *else return 0
  */
int   SymTable_contains(SymTable_T oSymTable, const char *pcKey){
   Node_t *current = oSymTable -> head;
   printf("%s\n", current -> key);
   assert(oSymTable != NULL);
   assert(pcKey != NULL);
   while(current != NULL){
      if(strcmp(current -> key, pcKey) == 0){
        return 1; /*Found*/
      }
      current = current -> next;
   }
   return 0; /*Not found*/
 }

/*
 *Returns the vaule of the binding with key
 *pcKey or NULL if there isnt any binding
 *with that key
 */
 void* SymTable_get(SymTable_T oSymTable, const char *pcKey){
  Node_t *current = oSymTable -> head;
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

   while(current != NULL){
     /*Den simferei na to kanoyme me tin contains
    epeidi tha eixame loop mesa se loop kai ara O(n^2)*/
     if( strcmp(current -> key, pcKey) == 0){
       return (void*)(current -> value);
     }
     current = current -> next;
   }
  return NULL;
 }

/*
 *Apply the pfApply function on every binding, with pvExtra as a parameter
 */
 void  SymTable_map(SymTable_T oSymTable,
                    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
                    const void *pvExtra){

       Node_t *current = oSymTable -> head;

       assert(oSymTable != NULL);
       assert(pfApply != NULL);
       while (current != NULL) {
         (*pfApply)(current -> key, (void*)current -> value, (void*)pvExtra);
         current = current -> next;
       }

}
