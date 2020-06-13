#include <stdlib.h>
#include "librere.h"

#define OUT_OF_BOUNDS -1
#define EMPTY_LIST -2

typedef struct Node 
{
	void *value;
	struct Node *previous;
	struct Node *next;	
		
} Node;

struct LinkedList 
{
	Node *next;
};

/* Declaration of utility methods, only visible in this "class"  */
static Node *LinkedList_get_last_node(LinkedList *self);
static Node *LinkedList_get_node_at(LinkedList *self, unsigned index);
static Node *Node_create(void *value, Node *previous);
static int LinkedList_check_index(LinkedList *self, unsigned index);

/* Method definition */

LinkedList *LinkedList_create(void)
{
	LinkedList *new_list = malloc(sizeof(LinkedList));
	new_list->next = NULL;	
	
	return (new_list);	
}

unsigned LinkedList_add(LinkedList *self, void *value)
{
	Node *last_node;
	unsigned index;

	index = LinkedList_get_size(self);

	last_node = LinkedList_get_last_node(self);
	if (last_node == NULL)
	{
		self->next = Node_create(value, NULL);
		return (index);
	}
	last_node->next = Node_create(value, last_node);
	return (index);
}

unsigned LinkedList_set(LinkedList *self, void *value, unsigned index)
{
	if (LinkedList_check_index(self, index))
	{
		LinkedList_get_node_at(self, index)->value = value;
		return (index);
	}		
	return (OUT_OF_BOUNDS);
}


unsigned LinkedList_remove(LinkedList *self, unsigned index)
{
	Node *node;
	unsigned list_len;

	list_len = LinkedList_get_size(self);

	if (LinkedList_check_index(self, index))
	{	

		if (index == 0)
		{
			if (list_len == 1)
			{
				free(self->next);
				self->next = NULL;
			}
			else
			{
				node = self->next;
				self->next = self->next->next;
				free(node);
				node = NULL;
			}	
			return (0);
		}

		if ((node = LinkedList_get_node_at(self, index)) != NULL)
		{
			if (list_len > index)
			{
				node->next->previous = node->previous;
			}
			node->previous->next = node->next;
			free(node);
			node = NULL;

			return (index);
		}
	}

	return (OUT_OF_BOUNDS);	
}

unsigned LinkedList_remove_range(LinkedList *self, unsigned lowerbound, 
unsigned upperbound)
{
	if (lowerbound >= upperbound)
	{
		r_puterr("LinkedList_remove_range: lowerbound can't be greater or equal"
				"to upperbound. lowerbound is ");
		r_put_int(lowerbound);
		r_puterr(" and upperbound is ");
		r_put_int(upperbound);
		r_puterr("\n");
	
		return (OUT_OF_BOUNDS);	
	}
	
	if (LinkedList_check_index(self, upperbound))
	{
		Node *lower_node;
		Node *upper_node;

		lower_node = LinkedList_get_node_at(self, lowerbound);
		upper_node = LinkedList_get_node_at(self, upperbound);

		if (lowerbound != 0)
		{
			lower_node->previous->next = upper_node;
		}
		else
		{
			self->next = upper_node;
		}

		while (lower_node != upper_node)
		{
			lower_node  = lower_node->next;
			free(lower_node->previous);
			lower_node->previous = NULL;
		}

		return (upperbound - lowerbound - 1);	
	}

	return (OUT_OF_BOUNDS);
	
}

unsigned LinkedList_insert(LinkedList *self, void *value, unsigned index)
{
	Node *node;
	Node *new_node;

	if (index == 0)
	{
		node = self->next;
		new_node = Node_create(value, NULL);
		new_node->next = node;
		node->previous = new_node;
		self->next = new_node;

		return (0);	
	}

	if (LinkedList_check_index(self, index))
	{
		if ( (node = LinkedList_get_node_at(self, index)) != NULL)
		{
			new_node = Node_create(value, node->previous);
			new_node->next = node;
			node->previous->next = new_node;
			node->previous = new_node;

			return (index);
		}				
	}

	return (OUT_OF_BOUNDS);
}

void *LinkedList_get_at(LinkedList *self, unsigned index)
{
	if (LinkedList_check_index(self, index))
	{
		return ( LinkedList_get_node_at(self, index)->value );	
	}

	return (NULL);	
}

unsigned LinkedList_get_size(LinkedList *self)
{
	Node *current_node;
	unsigned count;
	
	current_node = self->next; 
	count = 0;
	while (current_node != NULL)
	{
		current_node = current_node->next;
		count++;	
	}

	return (count);
}

void LinkedList_print_debug(LinkedList *self)
{
	Node *current_node;
	unsigned count;

	count = 0;	
	r_print_address(self);
	r_putstr(": \n[\n");	
	if ((current_node = self->next) != NULL)
	{
		while (current_node != NULL)
		{
			r_putchar('\t');
			r_put_int(count++);
			r_putstr(" (");
			r_print_address(current_node);
			r_putstr(")");						
			if (current_node->next != NULL)
			{
				r_putstr("\n\t-------------------------\n");
			}
			current_node = current_node->next;
		}
	}	
	r_putstr(" \n]\n");
} 


void LinkedList_foreach(LinkedList *self, void (*function)(void *value))
{
	Node *current_node; 

	current_node = self->next;
	while (current_node != NULL)
	{
		(*function)(current_node->value);
		current_node = current_node->next;
	}
}


void LinkedList_map(LinkedList *self, void *(*mapping_function)(void *value) )
{	
	Node *current_node; 

	current_node = self->next;
	while (current_node != NULL)
	{
		current_node->value = (*mapping_function)(current_node->value);
		current_node = current_node->next;
	}	
}

void LinkedList_destroy(LinkedList **self)
{
	Node *last_node;
	
	last_node = LinkedList_get_last_node(*self);		

	if (last_node != NULL)
	{
		while (last_node->previous != NULL)
		{
			last_node = last_node->previous;
			free(last_node->next);
			last_node->next = NULL;
		}	
		free( (*self)->next);
		(*self)->next = NULL;
	}
	free(*self);	
	*self = NULL;
}


static Node *Node_create(void *value, Node *previous)
{
	Node *new_node = malloc(sizeof(Node));
	new_node->next = NULL;
	new_node->previous = previous;
	new_node->value = value;

	return (new_node);
}

static Node *LinkedList_get_last_node(LinkedList *self)
{
	Node *current_node = self->next;

	/* There's no node */
	if (current_node == NULL) 
	{
		return (NULL);
	}
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	return (current_node);	
}

static Node *LinkedList_get_node_at(LinkedList *self, unsigned index)
{
	unsigned list_length, count, mid;
	Node *node;

	list_length = LinkedList_get_size(self) - 1;

	if (index > list_length)
	{
		return (NULL);
	}	

	count = 0;
	mid = list_length / 2;

	if (index >= mid)
	{
		node = LinkedList_get_last_node(self); 
		count = list_length;
		while (count-- > index)
		{
			node = node->previous;	
		} 
		return (node);
	}
	
	else 
	{
		node = self->next;
		if (node == NULL)
		{
			return (NULL);
		}
		count = 0; 
		while (count++ < index)
		{
			node = node->next;
		}
		return (node);	
	}	
}

static int LinkedList_check_index(LinkedList *self, unsigned index)
{
	unsigned list_len;

	if (index > (list_len = LinkedList_get_size(self)) - 1)
	{			
		r_puterr("LinkedList_get_at: index out of bounds - list upper bound is ");
		r_put_int(list_len - 1);
		r_puterr(" while index is ");
		r_put_int(index);
		r_putchar('\n');
		return (OUT_OF_BOUNDS);
	}

	return (1);
}

