#include <JsonParser.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

bool	strIsNbr(char *nbr)
{
	int i = 0;

	for (; nbr[i] == '+' || nbr[i] == '-'; i++);
	for (; isdigit(nbr[i]); i++);
	return (nbr[i] == 0 && i != 0 && isdigit(nbr[i - 1]));
}

int	displayJsonElement(char *path, char *key)
{	//Parse the file
	JsonParserResult	result = JsonParser_parseFile(path, JSON_TO_ARRAY);

	//Verify if an error occured
	if (result.error) {
		printf("%s: %s\n", path, result.error);
		JsonParser_destroyData(result.data, result.type);
		return EXIT_FAILURE;
	}

	//Display the file if no key was given
	if (!key) {
		JsonParser_printElement(result.data, result.type, NULL);
		JsonParser_destroyData(result.data, result.type);
		return EXIT_SUCCESS;
	}

	//Verify the content type
	if (result.type == JsonParserObjType) {
		const JsonParserObj	*object = JsonParserObj_getElement(result.data, key);

		//Verify if this object has the key
		if (!object) {
			printf("%s: The key \"%s\" doesn't exist in this file", path, key);
			JsonParser_destroyData(result.data, result.type);
			return EXIT_FAILURE;
		} else
			JsonParser_printElement(object->data, object->type, NULL);
	} else if (result.type == JsonParserListType && strIsNbr(key)) {
		const JsonParserList	*list = JsonParserList_getElement(result.data, atoi(key));

		if (!list) {
			printf("%s: The key \"%s\" doesn't exist in this file", path, key);
			JsonParser_destroyData(result.data, result.type);
			return EXIT_FAILURE;
		} else
			JsonParser_printElement(list->data, list->type, NULL);
	} else if (result.type == JsonParserListType)
		printf("%s: Only integer keys are valid for arrays", path);
	else
		printf("%s: Only array and objects can have a key", path);
	JsonParser_destroyData(result.data, result.type);
	return EXIT_SUCCESS;
}

int	main(int argc, char *argv[])
{
	if (argc <= 1 || argc >= 4) {
		printf("Usage: %s <file.json> <key>\n", argv[0]);
		return EXIT_SUCCESS;
	}
	return (displayJsonElement(argv[1], argc == 3 ? argv[2] : NULL));
}