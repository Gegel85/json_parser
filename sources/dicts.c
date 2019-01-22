#include <string.h>
#include <malloc.h>
#include "JsonParser.h"

JsonParserObj	*JsonParserObj_getElement(JsonParserObj *list, char *index)
{
	for (; list; list = list->next)
		if (strcmp(list->index, index) == 0)
			return (list);
	return (NULL);
}

bool	JsonParserObj_addElement(JsonParserObj *list, void *data, JsonParserTypes type, char *index)
{
	JsonParserString	buffer;
	
	for (; list->next; list = list->next) {
		if (!list->index)
			break;
		if (strcmp(list->index, index) == 0)
			return (false);
	}
	if (list->index && strcmp(list->index, index) == 0) {
		free(index);
		return (false);
	}
	if (list->index) {
		list->next = malloc(sizeof(*list->next));
		if (!list->next)
			return (false);
		list->next->next = NULL;
		list->next->prev = list;
		list = list->next;
	}
	if (type == JsonParserStringType) {
		buffer.length = strlen(data);
		buffer.content = strdup(data);
		list->data = JsonParser_copyData(&buffer, type);
	} else
		list->data = JsonParser_copyData(data, type);
	list->index = strdup(index);
	list->type = type;
	return (true);
}

void	destroyObjEntry(JsonParserObj *list)
{
	JsonParserObj	buff;

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

void	JsonParserObj_delElement(JsonParserObj *list, char *index)
{
	for (; list; list = list->next)
		if (strcmp(list->index, index) == 0) {
			destroyObjEntry(list);
			return;
		}
}
void	JsonParserObj_destroy(JsonParserObj *list)
{
	for (; list->next; list = list->next) {
		free(list->index);
		if (list->prev)
			free(list->prev);
		JsonParser_destroyData(list->data, list->type);
	}
	JsonParser_destroyData(list->data, list->type);
	if (list->prev)
		free(list->prev);
	free(list->index);
	free(list);
}