#include "librere.h"

void r_print_address(void *memory_location)
{
	r_putstr("0x");
	r_putstr(r_str_tolower(r_itohex((long)memory_location)));
}
