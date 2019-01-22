#include <string.h>
#include "concatf.h"

char	*my_show_str(char *str)
{
	return (str ? showstr(str) : strdup("(null)"));
}

char	*my_put_str(char *str)
{
	return (str ? strdup(str) : strdup("(null)"));
}