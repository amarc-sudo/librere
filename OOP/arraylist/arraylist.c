#include "librere.h"
#include <stdlib.h>

#define OUT_OF_BOUNDS -1

static void copy_list_content(ArrayList **src, unsigned dest_size);
static void display_out_of_bounds(char *function_name, unsigned index,
		unsigned upperbound);

struct ListBase
{
	void **content;
	unsigned length;
};

/* 
 * Appends `element` at the end of `list` and returns the index of the added 
 * element ( which's `ArrayList_get_length() - 1` ).
*/

unsigned ArrayList_add(ArrayList **pointer_to_list, void *element)
{

	ArrayList *list = *pointer_to_list;
	r_putstr("\n-- start --\n");
	r_putstr((char *)element);
	r_putstr("\n-- end --\n");

	/*if (!list->length)
	{
		list->content = malloc(sizeof(void *));
		*list->content = element;
		list->length = 1;
		return (0);
	}*/


	copy_list_content(pointer_to_list, list->length + 1);
	list->content[list->length - 1] = element;
	printf("%s", (void *)list->content[0]);	
	return (list->length - 1);
}

/*
 * Creates an **instance** of `ArrayList` and returns a pointer to it. This 
 * pointer will need to be passed all over the functions that deal with 
 * ArrayLists. 
*/

ArrayList *ArrayList_create(void)
{
	ArrayList *list;

	list = malloc(sizeof(ArrayList));
	list->length = 0;
	list->content = NULL;

	return (list);	
}


/*
 * Process each element of `list` with `function`. `function` must take a single
 * `void *` argument corresponding to each individual element of `list`. 
 * This is often used to print the entire list.
 * You can see a common use of this function in the Getting Started section.
*/

void ArrayList_foreach(ArrayList *list, void(*function)(void *element))
{
	for (unsigned i = 0; i < list->length; ++i)
	{
		(*function)(list->content[i]);
	}
}


/*
 * Get element of `list` at index `index`, as long as `index` is not out of the i
 * bounds of the list. Returns the element (a `void *`) or `NULL` if error.
*/


void *ArrayList_get_at(ArrayList *list, unsigned index)
{
	if (index < list->length)
	{
		return (list->content[index]);	
	}

	display_out_of_bounds("ArrayList_get_at", index, list->length - 1);
	return (NULL);
}


/*
 * Returns the length of `list`.
*/


unsigned ArrayList_get_length(ArrayList *list)
{
	return (list->length);
}



unsigned ArrayList_insert()
{
	return (0);
}


/*
 * Process each element of `list` with `mapping_function` and replaces it by the 
 * value returned by `mapping_function`. Heavily used to do some massive changes 
 * of the same kind on all the elements of a list.
*/


void ArrayList_map(ArrayList *list, void *(*function)(void *element))
{
	for (unsigned i = 0; i < list->length; i++)
	{
		list->content[i] = (*function)(list->content[i]);
	}
}


/*
 * Removes element at position `index` in `list`. If it exists, returns the 
 * index where was the deleted element, `-1` otherwise.
*/


unsigned ArrayList_remove(ArrayList *list, unsigned index)
{
	if (index < list->length)
	{
		ArrayList *new_list;

		list->content[index] = NULL;
		//new_list = ArrayList_copy(list, list->length - 1);
		free(list);
		list = new_list;
		
		return (index);
	}
	display_out_of_bounds("ArrayList_remove", index, list->length - 1);

	return (-1);
}


/*
 * Removes all elements between positions `lowerbound` and `upperbound`
 * (both inclusive) from `list`. Returns the number of elements removed, `-1` 
 * if failure. 
*/


int ArrayList_remove_range(ArrayList *list, unsigned lowerbound,
		unsigned upperbound)
{
	if (upperbound > lowerbound)
	{
		if (upperbound < list->length)
		{
			int nb_elements;
			ArrayList *new_list;

			nb_elements = upperbound - lowerbound + 1;

			for (unsigned i = lowerbound; i <= upperbound; i++)
			{
				list->content[i] = NULL;
			}

			//new_list = ArrayList_copy(list, list->length - nb_elements);
			free(list);
			list = new_list;

			return (nb_elements);	
		}
		display_out_of_bounds("ArrayList_remove_range", upperbound, list->length -1 );

		return (OUT_OF_BOUNDS);
	}

	r_putstr("ArrayList_remove_range: detected lowerbound greater or equal"
		 	 " than upperbound: illegal parameter values, did nothing.\n");

	return (-2);
}


/* 
 * Set element at index `index` of `list` to `element`. Returns `index` if 
 * successful, `-1` if error.
*/


int ArrayList_set(ArrayList *list, void *element, unsigned index)
{
	if (index < list->length)
	{
		list->content[index] = element;
		return (index);
	}

	display_out_of_bounds("ArrayList_set", index, list->length - 1);

	return (-1);
}


/*
* HELPER METHODS 
*/


/*
 * Passing src by reference 
*/
static void copy_list_content(ArrayList **src, unsigned dest_len)
{
	unsigned i;
	ArrayList *old_list;
	ArrayList *new_list;

	old_list = *src;
	new_list = ArrayList_create();
	new_list->content = (void **) malloc(sizeof(void *) * dest_len);
	
	i = 0;
	while (i < old_list->length)
	{
		void *temp;

		if ( (temp = *old_list->content++) != NULL)
		{
			new_list->content[i] = temp;
			++i;
		}			
	}
	
	new_list->length = dest_len;
	*src = new_list;
	printf("dest_len is %d\n", dest_len);
}

static void display_out_of_bounds(char *function_name, unsigned index,
		unsigned upperbound)
{
	r_putstr(function_name);
	r_putstr(": INDEX OUT OF BOUNDS -> specified index is ");
	r_put_int(index);
	r_putstr(" while list's upperbound is ");
	r_put_int(upperbound);
	r_putstr(".\n");
}


