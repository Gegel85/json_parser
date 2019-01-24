#include <malloc.h>
#include "JsonParser.h"

float	JsonParserFloat_toFloat(const JsonParserFloat *value)
{
	return (*value);
}

void	JsonParserFloat_destroy(JsonParserFloat *value)
{
	free(value);
}