#ifndef SYMTABLE_H_
#define SYMTABLE_H_
#include <stdio.h>

typedef struct SymTable *SymTable_T;
/*
 *Returns a new empty Symtable (with no bindings)
 */
SymTable_T SymTable_new(void);

/*
 *Free all memory that oSymTable uses
 */
void SymTable_free(SymTable_T oSymTable);

/*
 *Returns the number of bindings in symtable(length)
 */
unsigned int SymTable_getLength(SymTable_T oSymTable);

/*
 *If there isnt any binding with the same key a new
 *binding will be added with key pcKey and value
 *pvValue. Return 1 if success else return 0
 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

/*
 *If there is a binding with key pcKey it will SymTable_remove
  *the binding and return 1(TRUE) else return(TRUE)
 */
int   SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*
 *Returns 1 if the Symtable contains the binding with pcKey
 *else return 0
 */
int   SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/*
 *Returns the vaule of the binding with key
 *pcKey or NULL if there isnt any binding
 *with that key
 */
void* SymTable_get(SymTable_T oSymTable, const char *pcKey);

/*
 *Apply the pfApply function on every binding, with pvExtra as a parameter
 */
void  SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra);
#endif
