#include <malloc.h>
#include "JsonParser.h"

bool	JsonParserBoolean_toBool(JsonParserBoolean *value)
{
	return (*value);
}

void	JsonParserBoolean_destroy(JsonParserBoolean *value)
{
	free(value);
}