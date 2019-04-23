NAMES =	json_parser	\
		json_nice	\
		json_creator\
		json_parser_cpp\

FILE =	json_parser.c	\
        json_nice.c		\
        json_creator.c	\

SRC =	$(FILE:%.c=%.o)

OBJ =	$(SRC:.c=.o) main.o

INC =	-I../include

LD_FLAGS = -ljson_parser -L ..

CC =	gcc

CFLAGS=	$(INC)	\
	-W	\
	-Wall	\
	-Wextra	\

CXX =	g++

CXXFLAGS=	$(INC)	\
	-W	\
	-Wall	\
	-Wextra	\

all:	$(OBJ) $(NAMES)

json_parser:
	$(CC) -o json_parser json_parser.o $(LD_FLAGS)

json_nice:
	$(CC) -o json_nice json_nice.o $(LD_FLAGS)

json_creator:
	$(CC) -o json_creator json_creator.o $(LD_FLAGS)

json_parser_cpp:
	$(CXX) -o json_parser_cpp main.o -ljson_parser_cpp $(LD_FLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAMES) $(NAMES:%=%.exe)

re:	fclean all

dbg:	CXXFLAGS += -g -O0
dbg:	CFLAGS += -g -O0
dbg:	re

PIC:	all