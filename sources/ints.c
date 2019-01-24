#include <malloc.h>
#include "JsonParser.h"

int	JsonParserInt_toInt(const JsonParserInt *value)
{
	return (*value);
}

void	JsonParserInt_destroy(JsonParserInt *value)
{
	free(value);
}