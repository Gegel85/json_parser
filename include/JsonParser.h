#ifndef __PARSING_HEADER_
#define __PARSING_HEADER_

#include <stdbool.h>

typedef enum {
	JsonParserBooleanType,
	JsonParserStringType,
	JsonParserFloatType,
	JsonParserArrayType,
	JsonParserObjType,
	JsonParserListType,
	JsonParserIntType,
	JsonParserNullType,
} JsonParserTypes;

typedef bool    JsonParserBoolean;
typedef float   JsonParserFloat;
typedef int     JsonParserInt;

typedef struct {
	char	*content;
	int	length;
} JsonParserString;	//String

typedef struct StructParserObj JsonParserObj;
struct StructParserObj {
	char		*index;
	void		*data;
	JsonParserTypes	type;
	JsonParserObj	*next;
	JsonParserObj	*prev;
};

typedef struct StructParserList JsonParserList;
struct StructParserList {
	void		*data;
	JsonParserTypes	type;
	JsonParserList	*next;
	JsonParserList	*prev;
};		//Double linked list

typedef struct {
	void		*content;
	int		length;
	JsonParserTypes	type;
	JsonParserList	*list;
} JsonParserArray;	//An array

typedef struct {
	void		*data;	//This is NULL when something went wrong
	JsonParserTypes	type;
	char		*error;	/*This is NULL if everything went good
				  (So if data is NULL, error shouldn't be)
				  This is the error found when parsing the file or string*/
} JsonParserResult;

typedef struct {
	char	objOpen;              //The obj opening character     (by default it's '{')
	char	objClose;             //The obj closing character     (by default it's '}')
	char	arrOpen;              //The array opening character   (by default it's '[')
	char	arrClose;             //The array opening character   (by default it's ']')
	char	separator;            //The separator character       (by default it's ',')
	char	eqChar;               //The equal char                (by default it's ':')
	char	*strChar;             //The string chars              (by default it's '"' and ''')
	char	*singLineComment;     //Single line comments
	char	*multLineCommentStart;//Multi line comments start.
	char	*multLineCommentEnd;  //Multi line comments end.
	bool	listToArray;          /*By default, arrays are converted to linked lists.
                                        You can make lists become arrays. This is not recommended
                                        since lists containing different types will not be converted.
                                        You can still try to convert a list to an array later with
                                        ParserList_convertToArray(list)
                                        Note that this value is only used when parsing the JSON like string*/
	bool	compact;              /*If true, will take the least space as possible (no spaces, \n, ...)
  					Note that this value is only used when creating the JSON like string*/
} JsonParserInfos;

//This is a default configuration to parse some json files
#define JSON_COMPACT		((JsonParserInfos[1]) {{'{', '}', '[', ']', ',', ':', "\"'", "//", "/*", "*/", false, true}})
#define JSON_NOT_COMPACT	((JsonParserInfos[1]) {{'{', '}', '[', ']', ',', ':', "\"'", "//", "/*", "*/", false, false}})
#define JSON_TO_ARRAY		((JsonParserInfos[1]) {{'{', '}', '[', ']', ',', ':', "\"'", "//", "/*", "*/", true, false}})

/////////////////////
//Parsing functions//
/////////////////////

//////////////////////////////////////////////////////////////
//              Parse a file with it's path                 //
//If NULL is passed instead of an info structure, takes     //
//The default structure info.                               //
//                                                          //
//So a call to  JsonParser_parseFile(path, NULL) is like    //
//a call to     JsonParser_parseFile(path, JSON_COMPACT)    //
//////////////////////////////////////////////////////////////
JsonParserResult	JsonParser_parseFile(const char *path, JsonParserInfos *infos);

//////////////////////////////////////////////////////////////
//           Parse a NULL terminated string                 //
//If NULL is passed instead of an info structure, takes     //
//the default structure info.                               //
//                                                          //
//So a call to  JsonParser_parseString(path, NULL) is like  //
//a call to     JsonParser_parseString(path, JSON_COMPACT)  //
//////////////////////////////////////////////////////////////
JsonParserResult	JsonParser_parseString(const char *string, JsonParserInfos *infos);

//////////////////////////////////////////////////////////////
//            Dumps the structure to a file                 //
//If NULL is passed instead of an info structure, takes     //
//The default structure info.                               //
//                                                          //
//So a call to  JsonParser_parseFile(path, NULL) is like    //
//a call to     JsonParser_parseFile(path, JSON_COMPACT)    //
//////////////////////////////////////////////////////////////
bool	JsonParser_createFile(const char *path, const void *data, JsonParserTypes type, JsonParserInfos *infos);

//////////////////////////////////////////////////////////////
//           Create a NULL terminated string                //
//If NULL is passed instead of an info structure, takes     //
//the default structure info.                               //
//                                                          //
//So a call to  JsonParser_createString(path, NULL) is like //
//a call to     JsonParser_createString(path, JSON_COMPACT) //
//         If an error occurred, returns NULL               //
//////////////////////////////////////////////////////////////
char	*JsonParser_createString(const void *data, JsonParserTypes type, JsonParserInfos *infos);



/////////////////////////////
//Data management functions//
/////////////////////////////

//////////////////////////////////////////////////////////////
//          Destroys a data according to its type           //
//////////////////////////////////////////////////////////////
void	JsonParser_destroyData(void *data, JsonParserTypes type);

//////////////////////////////////////////////////////////////
//              Gets the size of a given type               //
//////////////////////////////////////////////////////////////
int	JsonParser_getSizeOf(JsonParserTypes type);

//////////////////////////////////////////////////////////////
//  Copy bytes of data and create a new buffer to store it  //
//////////////////////////////////////////////////////////////
void	*JsonParser_copyData(void *data, JsonParserTypes type);

//////////////////////////////////////////////////////////////
//   Returns a string describing the type. Don't free it !  //
//////////////////////////////////////////////////////////////
char	*JsonParser_typeToString(JsonParserTypes type);

//////////////////////////////////////////////////////////////
//                     Displays a data                      //
//////////////////////////////////////////////////////////////
void	JsonParser_printElement(const void *data, JsonParserTypes type, JsonParserInfos *infos);



/////////////////////////////////////////////////////
//          Array management functions             //
// /!\ These arrays are not NULL terminated !  /!\ //
//A 0 length array will see his pointer set to NULL//
//TLDR: Don't try to access < 1 length arrays      //
/////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//   Returns a pointer to the element at the index in the   //
//     array. If not in the array range, returns NULL.      //
//////////////////////////////////////////////////////////////
void	*JsonParserArray_getElement(const JsonParserArray *array, int index);

//////////////////////////////////////////////////////////////
//               Destroys the given array                   //
//////////////////////////////////////////////////////////////
void	JsonParserArray_destroy(JsonParserArray *array);



/////////////////////////////
//List management functions//
/////////////////////////////

//////////////////////////////////////////////////////////////
//  Transforms a JsonParserList into a JsonParserArray.     //
//  This will fail if all elements doesn't have the same    //
//  type. Returns an array of length -1 on failure.         //
//////////////////////////////////////////////////////////////
JsonParserArray	JsonParserList_toArray(JsonParserList *list);

//////////////////////////////////////////////////////////////
//    Returns a pointer to the link at the index or NULL    //
//    if not found                                          //
//////////////////////////////////////////////////////////////
const JsonParserList	*JsonParserList_getElement(const JsonParserList *list, int index);

//////////////////////////////////////////////////////////////
//   Add the given list to the index in the list. Returns   //
//       true if added successfully and false if not        //
//////////////////////////////////////////////////////////////
bool	JsonParserList_addElement(JsonParserList *list, void *data, JsonParserTypes type, int index);

//////////////////////////////////////////////////////////////
//         Deletes the given index in the list.             //
//////////////////////////////////////////////////////////////
void	JsonParserList_delElement(JsonParserList *list, int index);

//////////////////////////////////////////////////////////////
//                Destroys the given list                   //
//////////////////////////////////////////////////////////////
void	JsonParserList_destroy(JsonParserList *list);



////////////////////////////
//Obj management functions//
////////////////////////////

//////////////////////////////////////////////////////////////
//    Returns a pointer to the link at the index or NULL    //
//    if not found                                          //
//////////////////////////////////////////////////////////////
const JsonParserObj	*JsonParserObj_getElement(const JsonParserObj *list, char *index);

//////////////////////////////////////////////////////////////
//   Add the given list to the index in the list. Returns   //
//       true if added successfully and false if not        //
//////////////////////////////////////////////////////////////
bool	JsonParserObj_addElement(JsonParserObj *list, void *data, JsonParserTypes type, char *index);

//////////////////////////////////////////////////////////////
//         Deletes the given index in the list.             //
//////////////////////////////////////////////////////////////
void	JsonParserObj_delElement(JsonParserObj *list, char *index);

//////////////////////////////////////////////////////////////
//                 Destroys the given obj                   //
//////////////////////////////////////////////////////////////
void	JsonParserObj_destroy(JsonParserObj *list);



//////////////////////////////
//Float management functions//
//////////////////////////////

//////////////////////////////////////////////////////////////
//   Transform a JsonParserFloat type to a classic float    //
//////////////////////////////////////////////////////////////
float	JsonParserFloat_toFloat(const JsonParserFloat *value);

//////////////////////////////////////////////////////////////
//               Destroys the given float                   //
//////////////////////////////////////////////////////////////
void	JsonParserFloat_destroy(JsonParserFloat *value);



///////////////////////////////
//String management functions//
///////////////////////////////

//////////////////////////////////////////////////////////////
//  Transform a JsonParserString type to a classic char *   //
//////////////////////////////////////////////////////////////
char	*JsonParserString_toCharStar(const JsonParserString *value);

//////////////////////////////////////////////////////////////
//                Destroys the given int                    //
//////////////////////////////////////////////////////////////
void	JsonParserString_destroy(JsonParserString *value);



/////////////////////////////////
//Integers management functions//
/////////////////////////////////

//////////////////////////////////////////////////////////////
//     Transform a JsonParserInt type to a classic int      //
//////////////////////////////////////////////////////////////
int	JsonParserInt_toInt(const JsonParserInt *value);

//////////////////////////////////////////////////////////////
//                Destroys the given int                    //
//////////////////////////////////////////////////////////////
void	JsonParserInt_destroy(JsonParserInt *value);



////////////////////////////////
//Boolean management functions//
////////////////////////////////

//////////////////////////////////////////////////////////////
//   Transform a JsonParserBoolean type to a classic bool   //
//////////////////////////////////////////////////////////////
bool	JsonParserBoolean_toBool(const JsonParserBoolean *value);

//////////////////////////////////////////////////////////////
//               Destroys the given float                   //
//////////////////////////////////////////////////////////////
void	JsonParserBoolean_destroy(JsonParserBoolean *value);

#endif
