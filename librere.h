/* librere by Aurélien Brabant */

#ifndef LIBRERE_H

#define LIBRERE_H

#define r_isprintable(c) (c >= 32 && c <= 127) ? 1 : 0
#define r_isspace(c) (c == '\t' || c == '\n' || c == '\v' || \
					   c == '\f' || c == '\r' || c == ' ') ? 1 : 0 
#define r_isdigit(c) (c >= '0' && c <= '9') ? 1 : 0
#define r_isupper(c) (c >= 'A' && c <= 'Z') ? 1 : 0
#define r_tolower(c) (c + 32)

/* SORT */
int 	r_treesort(int *array, int length, char order);

/* CONVERSION */
int r_atoi(char *string);
char *r_itoa(int nb_to_convert);
char *r_itohex(long nb_to_convert);
char *r_itob(int number, char *base_charset);
int  r_btoi(char *string, char *base_charset);
char *r_btob(char *string, char *src_base_charset, char *dest_base_charset);

/* STRING */
int 	r_strlen(char *string);
char 	*r_str_reverse(char *string);
int 	r_charindex(char character, char *string);
int     r_charoccur(char character, char *string);
char 	*r_str_tolower(char *string);

/* PRINT  */
void 	r_put_int(int nb_to_print);
int 	r_putchar(char c);
void 	r_putstr(char *string);
void 	r_puterr(char *string);
void 	r_print_address(void *memory_location);
void	r_print_null(char *str);

/* UTIL */
int 	r_intlen(long number);
int     r_intbaselen(long number, int base);

/* LIST */

/* LINKED LIST */
typedef struct LinkedList 	LinkedList;
LinkedList 					*LinkedList_create(void);
void 						LinkedList_destroy(LinkedList **list);
void 						*LinkedList_get_at(LinkedList *list, unsigned index);
unsigned 					LinkedList_add(LinkedList *list, void *value);
void 						LinkedList_add_array(LinkedList *list, void *array, unsigned length);
void 						LinkedList_foreach(LinkedList *list, void (*function)(void *value));
void 						LinkedList_map(LinkedList *list, void *(*mapping_function)(void *value));
int 						*LinkedList_to_array(LinkedList *list);
unsigned 					LinkedList_get_size(LinkedList *list);
unsigned 					LinkedList_insert(LinkedList *list, void *value, unsigned index);
unsigned 					LinkedList_remove(LinkedList *list, unsigned index);
void 						LinkedList_print_debug(LinkedList *list);
unsigned 					LinkedList_set(LinkedList *list, void *value, unsigned index);
unsigned 					LinkedList_remove_range(LinkedList *list,
							unsigned lowerbound, unsigned upperbound);

/* ARRAY LIST */
typedef struct ListBase 	ArrayList;
ArrayList 					*ArrayList_create(void);
unsigned 					ArrayList_add(ArrayList **list, void *element);
void 						*ArrayList_get_at(ArrayList *list, unsigned index);
void 						ArrayList_foreach(ArrayList *list, 
							void (*function)(void *element));
unsigned 					ArrayList_get_length(ArrayList *list);
unsigned 					ArrayList_remove(ArrayList *list, unsigned index);
void                        ArrayList_map(ArrayList *list, void *(*mapping_function)(void *element));
int 						ArrayList_remove_range(ArrayList *list, 
							unsigned lowerbound, unsigned upperbound);


#endif /* LIBRERE_H */
