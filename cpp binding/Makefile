NAME = libjson_parser_cpp.a

CXXFLAGS = -W -Wall -Wextra -I../include

CXX = g++

SRC =	JsonArray.cpp	\
		JsonBoolean.cpp	\
		JsonNumber.cpp	\
		JsonObject.cpp	\
		JsonParser.cpp	\
		JsonString.cpp	\

OBJ = $(SRC:%.cpp=%.o)

all:	$(NAME)

$(NAME):$(OBJ)
		$(AR) rc $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

dbg:	CXXFLAGS += -O0 -g
dbg:	re

PIC:	CXXFLAGS += -fPIC
PIC:	all
