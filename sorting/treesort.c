/*
 * Sort the passed int array using binary tree data structure 
*/

#include <stdlib.h>
#include <stdio.h>

#define PROG_NAME "treesort"
#define TOO_FEW_MSG "To few values in your array - there must be at least 2 values to perform sorting\n"
#define TOO_FEW_ERR 1

typedef struct tnode *Treeptr;

typedef struct tnode
{
    int value;
    Treeptr left;
    Treeptr right;
} Treenode;

Treeptr insert(Treeptr root, int value, char order);
void    store(Treeptr position, int *array, int *i);

/* Order specifies if sort is to be made in ascending (order=1) or descending (order=-1) order */
int r_treesort(int *array, int length, char order)
{
    if (length <= 1)
    {
        printf("%s: %s", PROG_NAME, TOO_FEW_MSG);
        return (TOO_FEW_ERR);
    }

    int     *array_start;
    int     *array_end;
    int     index;
    Treeptr root;

    array_start = array;
    array_end = array + length;
    index = 0;
    root = NULL;

    /* Populates the tree */
    while (array_start < array_end)
    {
       root = insert(root, *array_start++, order);
    }

    /* Store tree in array - basically make it sorted */
    store(root, array, &index);
    
    return (0);
}

Treeptr insert(Treeptr root, int value, char order)
{
    /* If current node doesn't exist */
    if (root == NULL)
    {
        root = (Treeptr) malloc(sizeof(Treenode)); /* Allocates memory for the node */
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    }
    /* If node value is less or equal than current value */
    else if (order == 1 ? value <= root->value : root->value < value)
    {
        root->left = insert(root->left, value, order);
    }
    /* If node value is greater than current value */
    else
    {
        root->right = insert(root->right, value, order);
    }
    
    return (root);
}

void store(Treeptr position, int *array, int *index)
{
    if (position != NULL)
    {
        store(position->left, array, index);
        array[(*index)++] = position->value;
        store(position->right, array, index);
    }
}
