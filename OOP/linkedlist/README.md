# LinkedList

LinkedList is a C pseudo-class granting easy data management
relying on the linked list data structure. It comes with a bunch of utilities,
allowing data to stay organised and mutable.

This document will list all the functions of this pseudo-class and explain
how they work. If you are only interested in a quick overview, the [Getting started](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#getting-started) section is the place to look at.

## (Very) important notes

1) In order to work properly, you need to compile your code using the `librere` library (`LinkedList` is part of it) of which you can download the source code at the root of this repository. All the installation instructions are explained in the README there. The use of this library is **strictly REQUIRED** as many features used by the LinkedList rely on it.
Compiling code using the library is as easy as 

 

       gcc -o executable *.c -I{LIB_DIRECTORY} -L{LIB_DIRECTORY} -lrere

	`LIB_DIRECTORY` is the path where your library is. Don't forget to `#include "librere"`to avoid warnings from the compiler !

2) Please note you're currently reading the document for the **generic** implementation of LinkedList, **which means that most of the operations  you're going to do will imply intensive type-casting**. Make sure you know how types work properly to avoid any unexpected behaviour. Check the documentation carefully, it will give a bunch of examples.

## Table of contents

1. [Getting started](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#getting-started)
2. [Functions](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#functions) 

## Getting started

Here's an example showing you how to create a LinkedList, add elements to it, and print each one one the standard output.

    #include <stdio.h> /* for printf */
    #include <stdlib.h> /* for malloc */
    #include "librere.h" /* for LinkedList */
    
    int main(void)
    {
    	/*
    	 * Declaration of helper functions (in main scope as only
    	 * main needs to know about them)
    	*/
    	void print_int(void *nb);
    	int *pointer_to_const(int nb);
    
    	LinkedList *list = LinkedList_create(); /* creates  list */
    
    	/* add numbers from 0 to 10 to the list through for loop */
    	for (int i = 0; i <= 10; ++i)
    	{
    		LinkedList_add(list, pointer_to_const(i)); /* add element */
    	}
    
    	/* Iterates over each element that gets processed by print_int */
    	LinkedList_foreach(list, print_int);
    
    	/* Destroys list, freeing all memory allocated to it */
    	LinkedList_destroy(&list);
    }
    
    /*
     * Allocates storage for an int and returns a pointer to it,
     * in order to deal with void pointers
    */
    int *pointer_to_const(int constant)
    {
    	int *number;
    
    	number = malloc(sizeof(int));
    	*number = constant;
    
    	return (number);
    }
    
    /*
     * Print routine
    */
    void print_int(void *number)
    {
	    /* casting void* to int* and dereferencing it */
    	printf("%d, ", *(int *)number); 	
    }
   One word about `pointer_to_const` method. As we are dealing with void pointers to provide generic support, we need to pass an address to the add function. Thus `LinkedList_add(list, 1)` will not work because `1` is a constant and we can't get its address. But we want an easy way to pass value to our add function, right ? To solve this problem, the `pointer_to_const` function allocates memory for one `int` (often 4 bytes) and returns a pointer to it. This way, we can simply call the function and easily add any "constant" to our LinkedList. 
However, something of this kind would have done the work pretty well too :

       int number = 54;
       LinkedList_add(list, &number);
But it requires to define a variable internally each time.

Even if this example is not the simplest possible, it shows you the potential of the LinkedList pseudo-class. Therefore, there's a bunch of other functions that will help you achieve what you want with your data. See below for rich documentation.

## Functions
[LinkedList_add](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_add) \
[LinkedList_create](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_create) \
[LinkedList_destroy](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_destroy) \
[LinkedList_foreach](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_foreach) \
[LinkedList_get_at](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_get_at) \
[LinkedList_get_size](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_get_size) \
[LinkedList_insert](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_insert) \
[LinkedList_map](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_map) 
[LinkedList_print_debug](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_print_debug) 
[LinkedList_remove](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_remove) 
[LinkedList_remove_range](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_remove_range) 
[LinkedList_set](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#linkedlist_set) 






### LinkedList_add



    unsigned LinkedList_add(LinkedList *self, void *value);

Add ``value`` to the linked list, appending it at the end. Returns the index of the new value, which is equal to `LinkedList_get_size(self)` (as it is before value get added)

### LinkedList_create

    LinkedList *LinkedList_create(void);
Creates a linked list and returns a pointer to it. Must be used whenever you want to initialise a LinkedList object. This pointer will need to be passed to every function dealing with LinkedList (as C hasn't implicit ``this`` feature).

### LinkedList_destroy

    void LinkedList_destroy(LinkedList **self);
Destroy the linked list by freeing the memory that has been allocated for each one of its member, as well as the LinkedList's memory itself. ``self`` is automatically
set to `NULL`. Note that we need to **pass in the address of the pointer to the list**, in order to pass it by reference and not by value (used to set `self` to `NULL`).

### LinkedList_foreach

    void LinkedList_foreach( LinkedList *self, void (*function)(void *element) );

   An attempt to provide easy iteration over the linked list. Passed function must return ``void`` and take a single ``void*`` as an argument, that will be each element of the linked list. ``element`` will be processed as described by `function`, as many time as list's size.
As C has no native implementation of lambda expressions, it is needed to define a function outside that will process each element. You can look at a simple implementation by reading the code sample in the [Getting started](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#getting-started) section.

### LinkedList_get_at

    void *LinkedList_get_at(LinkedList *self, unsigned index);
Returns the element at index ``index`` of `self`. If there's an error, for example if index is out of bounds, it returns a `NULL` pointer.

### LinkedList_get_size

    unsigned LinkedList_get_size(LinkedList *self);
Returns the length of `self`.

### LinkedList_insert

    unsigned LinkedList_insert(LinkedList *self, void *element, unsigned index);
Insert `element` at index `index` of `self`. Returns the index of the inserted `element`, or `OUT_OF_BOUNDS` (-1) when failure. As often with LinkedList, the issue is about index being out of bounds or list being empty. In all this cases -1 is returned.

For example :

	LinkedList *list = LinkedList_create();
	LinkedList_add(list, pointer_to_const(54));
	LinkedList_add(list, pointer_to_const(23));
	LinkedList_add(list, pointer_to_const(102));
    LinkedList_insert(my_list, pointer_to_const(300), 1);

If you wonder what `pointer_to_const` is, I recommend checking the [Getting started](https://github.com/AurelleGit/LibRere/tree/master/OOP/linkedlist#getting-started) section.
	
Will insert `300 ` at index `1`:

    54, 300, 23, 102

### LinkedList_map

    void LinkedList_map(LinkedList *self, void *(*mapping_function)(void *value));
Process each element of ``self`` through ``mapping_function`` and replace each element by the value returned by `mapping_function`.

For example:

	/* If you are sure its an integer list */
	
    void *square(void *number)
    {
	   int *p;
	
	   p = (int *)number;
	   *p *= *p; /* number power 2 */ 

		return (p); /* returning p, implicit casting to void* */
    }

    int main(void)
    {
	    LinkedList *list = LinkedList_create();
		
		for (int i = 0; i <= 5; i++)
		{
			LinkedList_add(list, pointer_to_const(i));	
		}
		LinkedList_map(list, square);
	}

Will give :

    1, 4, 9, 16, 25

  ### LinkedList_print_debug
  

    void LinkedList_print_debug(LinkedList *self);

Display debug informations about `self` : display address of the list and each element of it.

    	LinkedList *list = LinkedList_create();
		
		for (int i = 0; i <= 5; i++)
		{
			LinkedList_add(list, pointer_to_const(i));	
		}
		
		LinkedList_print_debug(list);
will output something of this kind (addresses will change)

        0x7fb0cec05790: //Address of the list
    [
    	0 (0x7fb0cec057b0)
    	-------------------------
    	1 (0x7fb0cec057e0)
    	-------------------------
    	2 (0x7fb0cec05810)
    	-------------------------
    	3 (0x7fb0cec05840)
    	-------------------------
    	4 (0x7fb0cec05870)
    	-------------------------
    	5 (0x7fb0cec058a0)
    ]


  ### LinkedList_remove
  

    unsigned LinkedList_remove(LinkedList *self, unsigned index);
Remove element at index `index` of `list`. Free the memory allocated and return previous index of the deleted element if successful. Otherwise, return -1.

  ### LinkedList_remove_range
  

    unsigned LinkedList_remove_range(LinkedList *self, unsigned lowerbound, unsigned upperbound);
Remove a range of elements in `self`, from index `lowerbound` (inclusive) to `upperbound` (**exclusive**).
Of course, `upperbound >= lowerbound` is illegal as well as any out of bounds index. 
Each element removed is freed.

  ### LinkedList_set

    unsigned LinkedList_set(LinkedList *self, void *element, unsigned index);
set element of `self` at index `index` to `element`. Note that the index must be valid. The index of the set element is returned, -1 if error. Storage allocated for the old element is not released. Thanks to that, you can keep a pointer to it. 
