#include <malloc.h>
#include <string.h>
#include "concatf.h"
#include "JsonParser.h"

const JsonParserList	*JsonParserList_getElement(const JsonParserList *list, int index)
{
	int		len = 0;

	for (const JsonParserList *buf = list; buf && (buf->data || buf->type == JsonParserNullType); buf = buf->next, len++);
	if (ABS(index) >= len)
		return NULL;
	index = (index % len + len) % len;
	for (int i = 0; i++ < index; list = list->next);
	return (list);
}

JsonParserArray	JsonParserList_toArray(JsonParserList *list)
{
	JsonParserArray	result = {NULL, 0, JsonParserBooleanType, list};
	int		len = 0;
	int		index = 0;

	result.type = list->type;
	if (!list->data)
		return (result);
	for (JsonParserList *l = list; l; l = l->next, len++)
		if (result.type != l->type)
			return ((JsonParserArray){NULL, -1, JsonParserBooleanType, NULL});
	result.content = malloc(len * JsonParser_getSizeOf(result.type));
	if (!result.content)
		return ((JsonParserArray){NULL, -1, JsonParserBooleanType, NULL});
	result.length = len;
	memset(result.content, 0, len * JsonParser_getSizeOf(result.type));
	for (JsonParserList *l = list; l; l = l->next, index += JsonParser_getSizeOf(result.type))
		for (int i = 0; i < JsonParser_getSizeOf(result.type) && l->data; i++)
			((char *)result.content)[i + index] = ((char *)l->data)[i];
	return (result);
}

bool	JsonParserList_addElement(JsonParserList *list, void *data, JsonParserTypes type, int index)
{
	JsonParserList	*buffer = NULL;
	JsonParserString	buff;
	int		len = 0;

	for (JsonParserList *buf = list; buf; buf = buf->next, len++);
	index = (index % len + len) % len;
	for (int i = 0; i++ < index; list = list->next);
	if (list->data) {
		buffer = list->next;
		list->next = malloc(sizeof(*list->next));
		if (!list->next)
			return (false);
		list->next->prev = list;
		list = list->next;
		list->next = buffer;
	}
	if (type == JsonParserStringType) {
		buff.length = strlen(data);
		buff.content = strdup(data);
		list->data = JsonParser_copyData(&buff, type);
	} else
		list->data = JsonParser_copyData(data, type);
	list->type = type;
	return (true);
}

void	destroyListEntry(JsonParserList *list)
{
	JsonParserList	buff;

	memset(&buff, 0, sizeof(buff));
	JsonParser_destroyData(list->data, list->type);
	if (!list->prev) {
		if (list->next) {
			buff = *list->next;
			buff.prev = NULL;
		}
		free(list->next);
		*list = buff;
		return;
	}
	list->prev->next = list->next;
	if (list->next)
		list->next->prev = list->prev;
	free(list);
}

void	JsonParserList_delElement(JsonParserList *list, int index)
{
	for (int i = 0; list; list = list->next)
		if (i++ == index) {
			destroyListEntry(list);
			return;
		}
}

void	JsonParserList_destroy(JsonParserList *list)
{
	if (!list->data && list->type != JsonParserNullType) {
		free(list);
		return;
	}
	for (; list->next; list = list->next) {
		if (list->prev)
			free(list->prev);
		JsonParser_destroyData(list->data, list->type);
	}
	if (list->prev)
		free(list->prev);
	JsonParser_destroyData(list->data, list->type);
	free(list);
}
