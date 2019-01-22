#include <malloc.h>
#include <stddef.h>
#include "JsonParser.h"

void	*JsonParserArray_getElement(JsonParserArray *array, int index)
{
	int	step = 0;

	if (index < 0 || index >= array->length)
		return (NULL);
	step = JsonParser_getSizeOf(array->type);
	return (array->content + step * index);
}

void	JsonParserArray_destroy(JsonParserArray *array)
{
	JsonParserList_destroy(array->list);
	free(array->content);
	free(array);
}