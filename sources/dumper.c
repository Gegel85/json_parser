#include <malloc.h>
#include <concatf.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "JsonParser.h"

static int	isInString(char c, const char *str)
{
	for (int i = 0; str[i]; i++)
		if (str[i] == c)
			return (i);
	return (-1);
}

char	*transformString(char *str, int length, JsonParserInfos *infos)
{
	char	*result = strdup("");
	char	*buffer = NULL;

	for (int i = 0; i < length; i++) {
		buffer = result;
		if (isInString(str[i], infos->strChar) != -1)
			result = concatf("%s\\%c", result, str[i]);
		else if (str[i] >= ' ' && str[i] != 127)
			result = concatf("%s%c", result, str[i]);
		else if (str[i] == '\n')
			result = concatf("%s\\n", result);
		else if (str[i] == '\r')
			result = concatf("%s\\r", result);
		else if (str[i] == '\a')
			result = concatf("%s\\a", result);
		else if (str[i] == '\b')
			result = concatf("%s\\b", result);
		else if (str[i] == '\v')
			result = concatf("%s\\v", result);
		else if (str[i] == '\t')
			result = concatf("%s\\t", result);
		else if (str[i] == '\f')
			result = concatf("%s\\f", result);
		else if (str[i] == '\e')
			result = concatf("%s\\e", result);
		else if (str[i] == '\0')
			result = concatf("%s\\x00", result);
		else
			result = concatf("%s\\x%s%x", result, (unsigned char)str[i] > 15 ? "" : "0", (unsigned char)str[i]);
		free(buffer);
	}
	return (result);
}

char	*dataToString(const void *data, JsonParserTypes type, JsonParserInfos *infos, int indentation)
{
	char	*indent = strdup("");
	char	*index = NULL;
	char	*result = NULL;
	char	*buffer = NULL;

	for (int i = 0; i < indentation; i++)
		indent = concat(indent, "\t", true, false);
	switch(type) {
	case JsonParserBooleanType:
		result = strdup(*(JsonParserBoolean *)data ? "true" : "false");
		break;
	case JsonParserStringType:
		buffer = transformString(((JsonParserString *)data)->content, ((JsonParserString *)data)->length, infos);
		result = concatf("%c%s%c", infos->strChar[0], buffer, infos->strChar[0]);
		free(buffer);
		break;
	case JsonParserFloatType:
		result = concatf("%f", *(JsonParserFloat *)data);
		break;
	case JsonParserArrayType:
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = infos->arrOpen;
		result[1] = 0;
		for (int i = 0; i < ((JsonParserArray *)data)->length; i++) {
			if (!infos->compact) {
				buffer = result;
				result = concatf("%s\n%s\t", result, indent);
				if (!result)
					return (NULL);
				free(buffer);
			}
			result = concat(result, dataToString(JsonParserArray_getElement(data, i), ((JsonParserArray *)data)->type, infos, indentation + 1), true, true);
			if (!result)
				return (NULL);
			buffer = result;
			result = concatf("%s%c", result, infos->separator);
			if (!result)
				return (NULL);
			free(buffer);
		}
		buffer = result;
		if (((JsonParserArray *)data)->length > 0)
			result = concatf("%s%s%s%c", result, infos->compact ? "" : "\n", infos->compact ? "" : indent, infos->arrClose);
		else
			result = concatf("%s%c", result, infos->arrClose);
		if (!result)
			return (NULL);
		free(buffer);
		break;
	case JsonParserObjType:
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = infos->objOpen;
		result[1] = 0;
		for (const JsonParserObj *list = data; list && (list->data || list->type == JsonParserNullType); list = list->next) {
			buffer = result;
			index = transformString(list->index, strlen(list->index), infos);
			if (!infos->compact)
				result = concatf("%s\n%s\t%c%s%c%c ", result, indent, infos->strChar[0], index, infos->strChar[0], infos->eqChar);
			else
				result = concatf("%s%c%s%c%c", result, infos->strChar[0], list->index, infos->strChar[0], infos->eqChar);
			free(index);
			free(buffer);
			if (!result)
				return (NULL);
			result = concat(result, dataToString(list->data, list->type, infos, indentation + 1), true, true);
			if (!result)
				return (NULL);
			buffer = result;
			result = concatf("%s%c", result, infos->separator);
			if (!result)
				return (NULL);
			free(buffer);
		}
		buffer = result;
		if (((JsonParserObj *)data)->data || ((JsonParserObj *)data)->type == JsonParserNullType)
			result = concatf("%s%s%s%c", result, infos->compact ? "" : "\n", infos->compact ? "" : indent, infos->objClose);
		else
			result = concatf("%s%c", result, infos->objClose);
		if (!result)
			return (NULL);
		free(buffer);
		break;
	case JsonParserListType:
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = infos->arrOpen;
		result[1] = 0;
		for (const JsonParserList *list = data; list && (list->data || list->type == JsonParserNullType); list = list->next) {
			if (!infos->compact) {
				buffer = result;
				result = concatf("%s\n%s\t", result, indent);
				if (!result)
					return (NULL);
				free(buffer);
			}
			result = concat(result, dataToString(list->data, list->type, infos, indentation + 1), true, true);
			if (!result)
				return (NULL);
			buffer = result;
			result = concatf("%s%c", result, infos->separator);
			if (!result)
				return (NULL);
			free(buffer);
		}
		buffer = result;
		if (((JsonParserList *)data)->data || ((JsonParserList *)data)->type == JsonParserNullType)
			result = concatf("%s%s%s%c", result, infos->compact ? "" : "\n", infos->compact ? "" : indent, infos->arrClose);
		else
			result = concatf("%s%c", result, infos->arrClose);
		if (!result)
			return (NULL);
		free(buffer);
		break;
	case JsonParserIntType:
		result = concatf("%i", *(JsonParserInt *)data);
		break;
	case JsonParserNullType:
		result = strdup("null");
		break;
	}
	free(indent);
	return (result);
}

char	*JsonParser_createString(const void *data, JsonParserTypes type, JsonParserInfos *infos)
{
	if (infos && !strlen(infos->strChar))
		return (NULL);
	return (dataToString(data, type, infos ? infos : JSON_COMPACT, 0));
}

bool	JsonParser_createFile(const char *path, const void *data, JsonParserTypes type, JsonParserInfos *infos)
{
	int	fd;
	bool	success = true;
	char	*buffer = NULL;

	buffer = JsonParser_createString(data, type, infos);
	remove(path);
	fd = open(path, O_WRONLY | O_CREAT, 0664);
	if (fd < 0)
		return (false);
	if (!buffer)
		return (false);
	success = write(fd, buffer, strlen(buffer)) == (int)strlen(buffer);
	free(buffer);
	close(fd);
	return (success);
}

