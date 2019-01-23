NAME =	libjson_parser.a

FILE =	parser.c	\
		floats.c	\
		ints.c		\
		bools.c		\
		strings.c	\
		dicts.c		\
		data.c		\
		arrays.c	\
		lists.c		\
		dumper.c	\
		debug.c		\
		concat.c	\
        concatf.c	\
        float_to_str.c	\
        get_nbrlen.c	\
        int_to_str.c	\
        uint_to_str.c	\
        sub_strings.c	\
        str.c		\
        my_showstr.c	\
        my_putnbr_base.c\
        my_putstar.c	\
        my_putbase.c	\
        power.c		\

SRC =	$(FILE:%.c=sources/%.o)

OBJ =	$(SRC:.c=.o)

INC =	-Iinclude

CFLAGS=	$(INC)	\
	-W	\
	-Wall	\
	-Wextra	\

CC =	gcc

all:	$(NAME)
	$(MAKE) -C examples

$(NAME):$(OBJ)
	$(AR) rc $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C examples clean

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) -C examples fclean

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	re
