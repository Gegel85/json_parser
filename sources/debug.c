#include <malloc.h>
#include <stdio.h>
#include "JsonParser.h"

void	JsonParser_printElement(const void *data, JsonParserTypes type, JsonParserInfos *infos)
{
	char	*result = JsonParser_createString(data, type, infos ? infos : JSON_NOT_COMPACT);
	
	printf("%s\n", result);
	free(result);
}