#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define HASH_MULTIPLIER 65599

typedef struct BucketNode{
  const char *key;
  const void *value;
  struct BucketNode *next;
} Bucket_t;

typedef struct SymTable{

    int numberOfBuckets;
    int numberOfBindings;
    /*If same hash key insert in list with same hash key*/
    Bucket_t **bucketlist;
}SymTable;

/*Return a hash code for pcKey within the iBucketCount*/
static unsigned int SymTable_hash(const char *pcKey, unsigned int iBucketCount){
  size_t ui;
  unsigned int uiHash = 0U;
  for(ui = 0U; pcKey[ui] != '\0'; ui++){
    uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
  }

  return (int)(uiHash % (unsigned int)iBucketCount);
}

/*
 *Returns a new empty Symtable (with no bindings)
 */
 SymTable_T SymTable_new(void){
    SymTable_T oSymTable;/*The new oSymTable we will create*/
    size_t i;/*variable for loop*/

    /*Allocate memory for oSymTable and check for enough memory*/
    oSymTable = (SymTable_T)malloc(sizeof(SymTable));
    if(oSymTable == NULL){
      return NULL;
    }
    /*Starting number of buckets*/
    oSymTable -> numberOfBuckets = 509;
    oSymTable -> numberOfBindings = 0;
    /*Allocate memory for bucketlist*/
    oSymTable -> bucketlist = malloc((size_t)(oSymTable -> numberOfBuckets) * sizeof(Bucket_t*));
    /*Check if enough memory*/
    if(oSymTable -> bucketlist == NULL){
      free(oSymTable); /*Free the allocated memory for oSymTable and return NULL*/
      return NULL;
    }
    /*Make sure it doesnt point to somewhere unknown*/
    for(i = 0; i < oSymTable -> numberOfBuckets; i++){
      oSymTable -> bucketlist[i] = NULL;
    }
    /*Return the new oSymTable*/
    return oSymTable;
 }

 /*
  *Free all memory that oSymTable uses
  */
 void SymTable_free(SymTable_T oSymTable){
   int i;
   Bucket_t *current;

   assert(oSymTable != NULL);
   /*Go through every bucket*/
   for(i = 0; i < oSymTable -> numberOfBuckets; i++){
     current = oSymTable -> bucketlist[i];
     /*If bucket isnt NULL the free all bindings with the same hashkey*/
      if(oSymTable -> bucketlist[i] != NULL){
          while(current != NULL){
            current = oSymTable -> bucketlist[i];
            free((char*)current -> key);
            free(current);
            current = current -> next;
          }
      }
   }
   free(oSymTable -> bucketlist);
   free(oSymTable);
 }

 /*
  *Returns the number of bindings in symtable(length)
  */
  unsigned int SymTable_getLength(SymTable_T oSymTable){
  assert(oSymTable != NULL);
  return oSymTable -> numberOfBindings;
}

/*
 *If there isnt any binding with the same key a new
 *binding will be added with key pcKey and value
 *pvValue. Return 1 if success else return 0
 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
  int keyHash;
  const char *pcKeyCopy;
  Bucket_t *current;
  Bucket_t *newNode;

  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /*Allocate enough memory for a new Bucket_t*/
  newNode = (Bucket_t*)malloc(sizeof(Bucket_t));
  if(newNode == NULL){;
    return 0;/*Not enough memory*/
  }
  /*Allocate enough memory for pcKeyCopy with \0*/
  pcKeyCopy = (char*)malloc(strlen(pcKey) * sizeof(char) + 1);
  if(pcKeyCopy == NULL){
    return 0;/*Not enough memory*/
  }
  /*check if binding with key pcKey already exists
    and free alocated memory of newNode and keyCopy*/
  if( SymTable_contains(oSymTable, pcKey)){
    free(newNode);
    free((char*)pcKeyCopy);
    return 0;
  }
  /*Copy key to pcKeyCopy*/
  strcpy((char*)pcKeyCopy , (char*)pcKey);
  /*Generate a hashkey*/
  keyHash = SymTable_hash(pcKey, oSymTable -> numberOfBuckets);
  /*Check if we have a binding with same hashkey
    and then insert the binding in bucketlist*/
  if(oSymTable -> bucketlist[keyHash] != NULL){
      current = oSymTable -> bucketlist[keyHash];
      while (current != NULL) {
	 /*Binding with same key found and free allocated memory*/
  	 if( strcmp(current -> key, pcKey) == 0 ){
	     free((char*)pcKeyCopy);
	     free(newNode);
	 }
	 current = current -> next;
      }

     newNode -> key = pcKeyCopy;
     newNode -> value = pvValue;
     newNode -> next = oSymTable -> bucketlist[keyHash];
     oSymTable -> bucketlist[keyHash] = newNode;
     oSymTable -> numberOfBindings += 1;
     return 1;
  }
  else{
        newNode -> key = pcKeyCopy;
        newNode -> value = pvValue;
        newNode -> next = oSymTable -> bucketlist[keyHash];
        oSymTable -> bucketlist[keyHash] = newNode;
  }
oSymTable -> numberOfBindings += 1;
return 1;
}

/*
 *If there is a binding with key pcKey it will SymTable_remove
  *the binding and return 1(TRUE) else return(TRUE)
 */
int   SymTable_remove(SymTable_T oSymTable, const char *pcKey){
   int keyHash;
   Bucket_t *current;
   Bucket_t *prev;

   assert(oSymTable != NULL);
   assert(pcKey != NULL);

   keyHash = SymTable_hash(pcKey, oSymTable -> numberOfBuckets);
   current = oSymTable -> bucketlist[keyHash];
   while(current != NULL){
	prev = current;
	if(strcmp(current -> key, pcKey) == 0){
	   oSymTable -> bucketlist[keyHash] = current -> next;
	   free((char*)current -> key);
	   free(current);
	   oSymTable -> numberOfBindings -= 1;
	   return 1;/*Binding with key pcKey removed*/
	}
	else{
	   prev -> next = current -> next;
	   free((char*)current -> key);
	   free(current);
	   oSymTable -> numberOfBindings -= 1;
	   return 1;/*Binding with key pcKey removed*/
	}
     current = current -> next;
   }
 return 0;/*Binding with key pcKey not found*/
}

/*
 *Returns 1 if the Symtable contains the binding with pcKey
 *else return 0
 */
int   SymTable_contains(SymTable_T oSymTable, const char *pcKey){
  int keyHash;
  Bucket_t *current;

  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  keyHash = SymTable_hash(pcKey, oSymTable -> numberOfBuckets);
  current = oSymTable -> bucketlist[keyHash];

  while(current != NULL){
	if(strcmp(current -> key, pcKey) == 0){
		return 1;/*Binding with key pcKey found*/
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
  int keyHash;
  Bucket_t *current;

  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  keyHash = SymTable_hash(pcKey, oSymTable -> numberOfBuckets);
  current = oSymTable -> bucketlist[keyHash];

  while(current != NULL){
    if(strcmp(current -> key, pcKey) == 0){
        return (void*)current -> value;
    }
    current = current -> next;
  }
  return NULL;
}

/*
 *Apply the pfApply function on every binding, with pvExtra as a parameter
 */
void  SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra){
   int i;
   Bucket_t *current;

   assert(oSymTable != NULL);
   assert(pfApply != NULL);

   for(i = 0; i < oSymTable -> numberOfBuckets; i++){
     current = oSymTable -> bucketlist[i];
     while (current != NULL) {
       (*pfApply)(current -> key, (void*)current -> value, (void*)pvExtra);
       current = current -> next;
     }
   }
}
