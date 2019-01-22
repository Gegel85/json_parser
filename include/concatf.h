#ifndef __CONCATF_H_
#define __CONCATF_H_

#include <stdbool.h>
#include <stdarg.h>

#define ABS(x) (x < 0 ? -x : x)

char	*concatf(char *str, ...);
int	get_nbrlen(int nbr);
char	*concat(char *str1, char *str2, bool free1, bool free2);
char	*my_put_str(char *str);
char	*my_show_str(char *str);
char	*showstr(char const *str);
char    *uint_to_str(unsigned int nb);
char    *int_to_str(int nb);
char	*sub_strings(char const *str, int start, int end, char *buffer);
char	*my_putstarfloat(double *nbr, int format, int format_size);
char	*my_putstarint(int *nbr, int format, int format_size);
char	*my_putstarchar(char *c);
char	*my_putpointer(void *ptr, int format, int format_size);
char	*my_putnbr_unsigned(unsigned int *nbr, int format, int format_size);
char	*my_puthexa(int *nbr);
char	*my_puthexa_cap(int *nbr);
char	*my_putoctal(int *nbr);
char	*my_putbinary(int *nbr);
int	power(int, int);
char	*my_putnbrbase(unsigned int, char const *);
char	*float_to_str(double nbr, int decimals);

typedef struct {
	char	flag;
	int	type;
	char	*(*fct)(void *);
} flags;

#endif
