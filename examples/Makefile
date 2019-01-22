NAMES =	json_parser	\
		json_nice	\
		json_creator\

FILE =	json_parser.c	\
        json_nice.c		\
        json_creator.c	\

SRC =	$(FILE:%.c=%.o)

OBJ =	$(SRC:.c=.o)

INC =	-I../include

LD_FLAGS = -ljson_parser -L ..

CFLAGS=	$(INC)	\
	-W	\
	-Wall	\
	-Wextra	\

CC =	gcc

all:	$(OBJ) $(NAMES)

json_parser:
	$(CC) -o json_parser json_parser.o $(LD_FLAGS)

json_nice:
	$(CC) -o json_nice json_nice.o $(LD_FLAGS)

json_creator:
	$(CC) -o json_creator json_creator.o $(LD_FLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAMES) $(NAMES:%=%.exe)

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	re
