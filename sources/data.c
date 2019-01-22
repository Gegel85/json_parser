#include <stddef.h>
#include <malloc.h>
#include "JsonParser.h"

void	*JsonParser_copyData(void *data, JsonParserTypes type)
{
	int	size = JsonParser_getSizeOf(type);
	void	*new = size ? malloc(size) : NULL;

	if (new) {
		for (int i = 0; i < size; i++)
			((char *)new)[i] = ((char *)data)[i];
		if (type == JsonParserObjType && ((JsonParserObj *)data)->next)
			((JsonParserObj *)data)->next->prev = new;
		else if (type == JsonParserListType && ((JsonParserList *)data)->next)
			((JsonParserList *)data)->next->prev = new;
	}
	return (new);
}

char	*JsonParser_typeToString(JsonParserTypes type)
{
	switch(type) {
	case JsonParserBooleanType:
		return "boolean";
	case JsonParserStringType:
		return "string";
	case JsonParserFloatType:
		return "float";
	case JsonParserArrayType:
		return "array";
	case JsonParserObjType:
		return "object";
	case JsonParserListType:
		return "list";
	case JsonParserIntType:
		return "int";
	case JsonParserNullType:
		return "null";
	}
	return "Unknown";
}

int	JsonParser_getSizeOf(JsonParserTypes type)
{
	switch(type) {
	case JsonParserBooleanType:
		return sizeof(JsonParserBoolean);
	case JsonParserStringType:
		return sizeof(JsonParserString);
	case JsonParserFloatType:
		return sizeof(JsonParserFloat);
	case JsonParserArrayType:
		return sizeof(JsonParserArray);
	case JsonParserObjType:
		return sizeof(JsonParserObj);
	case JsonParserListType:
		return sizeof(JsonParserList);
	case JsonParserIntType:
		return sizeof(JsonParserInt);
	case JsonParserNullType:
		return 0;
	}
	return 0;
}

void	JsonParser_destroyData(void *data, JsonParserTypes type)
{
	if (!data)
		return;
	switch(type) {
	case JsonParserBooleanType:
		JsonParserBoolean_destroy(data);
		break;
	case JsonParserStringType:
		JsonParserString_destroy(data);
		break;
	case JsonParserFloatType:
		JsonParserFloat_destroy(data);
		break;
	case JsonParserArrayType:
		JsonParserArray_destroy(data);
		break;
	case JsonParserObjType:
		JsonParserObj_destroy(data);
		break;
	case JsonParserListType:
		JsonParserList_destroy(data);
		break;
	case JsonParserIntType:
		JsonParserInt_destroy(data);
		break;
	case JsonParserNullType:
		break;
	}
}
