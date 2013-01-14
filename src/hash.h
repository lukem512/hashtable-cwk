// Luke Mitchell

#ifndef HASH_H
#define HASH_H

#include "list.h"

// define the intial size for a hashtable
#define HASHTABLE_INITIAL_SIZE 2

// define the percentage utilisation threshold to be reached before resizing the table
#define HASHTABLE_UTILISATION_THRESHOLD 80

// data structure representing a  hashtable
typedef struct {
	int size;	// the size of the table
	int threshold;	// the threshold (%) at which the table size will be expanded
	int in_use;	// number of entries with data
	list** table;	
} hashtable;

// add/remove nodes
int 		hashtable_add_node 		(hashtable*, char*, int);
int		hashtable_remove_node		(hashtable*, char*);

// search table and get comparisons from search
int		hashtable_get_comparisons	(hashtable*, char*);
node*           hashtable_search       		(hashtable*, char*);

// ctor and dtor
hashtable*      hashtable_create                (void);
void 		hashtable_destroy		(hashtable*);

#endif
