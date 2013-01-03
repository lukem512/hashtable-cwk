// Luke Mitchell
// Linked List
// 22-11-2011
// edited 12/12/2011 for CW1 [100%]
// edited 27/12/2011 for CW2

#ifndef LIST_H
#define LIST_H

/* Includes */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Types */

typedef struct node {
	char	*data;
	int	count;
	struct node* next;
} node;

typedef struct list {
	int	size;
	node* 	start;
	node* 	end;
	node* 	current;
} list;

/* Function prototypes */

node*	list_search		(list*, char*);
int	list_get_comparisons	(list*, char*);
int	list_is_empty 		(list*);
void	list_reset		(list*);
int	list_add_node 		(list*, char*, int);
int	list_add_node_rear 	(list*, char*, int);
int	list_remove_node	(list*, node*);
int 	list_advance 		(list*);
int	list_retreat		(list*);
list*	list_create		(void);
void	list_destroy		(list*);

#endif
