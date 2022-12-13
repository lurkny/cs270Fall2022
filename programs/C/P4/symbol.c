#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  110 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author <b>Brody Larson</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      capacity;    /**< length of hast_table array                  */
  int      size;        /**< number of symbols (may exceed capacity)     */
  node_t** hash_table;  /**< array of head of linked list for this index */
  char**   addr_table;  /**< look up symbols by addr                     */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
sym_table_t* symbol_init (int capacity) {
  sym_table_t* table = (sym_table_t*) malloc(sizeof(sym_table_t));
  table->capacity = capacity;
  table->size = 0;
  table->hash_table = (node_t**) malloc(sizeof(node_t*) * capacity);

  for(int i = 0; i < capacity; i++){
    table->hash_table[i] = (node_t*) malloc(sizeof(node_t));
    table->hash_table[i]->next = NULL;
  }

  table->addr_table = (char**) malloc(sizeof(char*) * LC3_MEMORY_SIZE);

  return table;
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab) {
  //remove all symbols and free all allocated memory
  symbol_reset(symTab);
  free(symTab->hash_table);
  free(symTab->addr_table);
  free(symTab);
  return;
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab) {
  for(int i = 0; i < symTab->capacity; i++){
    node_t* current = symTab->hash_table[i];
    while(current != NULL){
      node_t* temp = current;
      current = current->next;
      free(temp);
    }
    symTab->hash_table[i] = NULL;
  }
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
  int hash;
  int index;
  if(symbol_search(symTab, name, &hash, &index) == NULL){
    node_t* Node = (node_t*) malloc(sizeof(node_t));
    Node->next = symTab->hash_table[index];
    symTab->hash_table[index] = Node;
    //set the hash and symbol
    Node->hash = hash;
    Node->symbol.name = strdup(name);
    Node->symbol.addr = addr;
    //set the addr_table
    symTab->addr_table[addr] = Node->symbol.name;
    symTab->size++;
    return 1;
  }
  return 0;
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
  *hash = symbol_hash(name);
  *index = *hash % symTab->capacity;
  node_t* current = symTab->hash_table[*index];
  while (current != NULL) {
    if (current->hash == *hash) {
      if(strcasecmp(current->symbol.name, name) == 0) {
        return current;
      }
    }
    current = current->next;
  }
  return NULL;
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
	int hash = 0;
	int index = 0;
	struct node* value = symbol_search(symTab, name, &hash, &index);	
	return &(value->symbol);
}



/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
  return symTab->addr_table[addr];
  
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
  for(int i = 0; i < symTab->capacity; i++){
    node_t* current = symTab->hash_table[i];
    while(current != NULL){
      if(current->symbol.name != NULL){
        (*fnc)(&current->symbol, data);

      }
      current = current->next;
    }

  }
  
}

/** @todo implement this function */
int symbol_size (sym_table_t* symTab) {
  return symTab->size;
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
  symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
  symbol_t* sym2 = *((symbol_t**) vp2);
  return strcasecmp(sym1->name, sym2->name);

  return 0;
}

/** @todo implement this function */
int compare_addresses (const void* vp1, const void* vp2) {
  //call back function for qsort

  symbol_t* sym1 = *((symbol_t**) vp1);
  symbol_t* sym2 = *((symbol_t**) vp2);
  if(sym1->addr == sym2->addr){
    return compare_names(vp1, vp2);
  }
  else if(sym1->addr > sym2->addr){
    return 1;
  }
  else{
    return -1;
  }

  return 0;
}

/** @todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order) {

  symbol_t** array = (symbol_t**) malloc(sizeof(symbol_t*) * symTab->size);
  int count = 0;
  for(int i = 0; i < symTab->capacity; i++){
    node_t* current = symTab->hash_table[i];
    while(current != NULL){
      if(current->symbol.name != NULL){
        array[count] = &current->symbol;
        count++;
      }
      current = current->next;
    }
  }
  if(order == HASH){
    return array;
  }
  else if(order == NAME){
    qsort(array, symTab->size, sizeof(symbol_t*), compare_names);
    return array;
  }
  else if(order == ADDR){
    qsort(array, symTab->size, sizeof(symbol_t*), compare_addresses);
    return array;
  }

  return NULL;
}

