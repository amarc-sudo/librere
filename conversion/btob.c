/* Convert a string in a base from another */

#include "librere.h"

char *r_btob(char *string, char *src_base_charset, char *dest_base_charset)
{
	return (r_itob(r_btoi(string, src_base_charset), dest_base_charset));
}
