#include <malloc.h>
#include "JsonParser.h"

char	*JsonParserString_toCharStar(const JsonParserString *value)
{
	return (value->content);
}

void	JsonParserString_destroy(JsonParserString *value)
{
	free(value->content);
	free(value);
}