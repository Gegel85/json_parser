#include "../include/JsonParser.hpp"
#include "../include/JsonBoolean.hpp"
#include "../include/JsonObject.hpp"
#include "../include/JsonNumber.hpp"
#include "../include/JsonString.hpp"
#include "../include/JsonArray.hpp"
#include "../include/JsonNull.hpp"

std::unique_ptr<JsonValue> JsonParser::convertValue(void *data, JsonParserTypes type)
{
	switch (type) {
	case JsonParserObjType:
		return std::unique_ptr<JsonValue>{new JsonObject(*reinterpret_cast<JsonParserObj *>(data))};
	case JsonParserArrayType:
		return std::unique_ptr<JsonValue>{new JsonArray(*reinterpret_cast<JsonParserArray *>(data))};
	case JsonParserListType:
		return std::unique_ptr<JsonValue>{new JsonArray(*reinterpret_cast<JsonParserList *>(data))};
	case JsonParserNullType:
		return std::unique_ptr<JsonValue>{new JsonNull()};
	case JsonParserStringType:
		return std::unique_ptr<JsonValue>{new JsonString(JsonParserString_toCharStar(reinterpret_cast<JsonParserString *>(data)))};
	case JsonParserIntType:
		return std::unique_ptr<JsonValue>{new JsonNumber(JsonParserInt_toInt(reinterpret_cast<JsonParserInt *>(data)))};
	case JsonParserFloatType:
		return std::unique_ptr<JsonValue>{new JsonNumber(JsonParserFloat_toFloat(reinterpret_cast<JsonParserFloat *>(data)))};
	case JsonParserBooleanType:
		return std::unique_ptr<JsonValue>{new JsonBoolean(JsonParserBoolean_toBool(reinterpret_cast<JsonParserBoolean *>(data)))};
	}
	throw InvalidTypeException("Invalid type given");
}

std::unique_ptr<JsonValue> JsonParser::parseFile(const std::string &path, JsonParserInfos *infos)
{
	JsonParserResult result = JsonParser_parseFile(path.c_str(), infos);

	if (result.error)
		throw InvalidJsonFileException(result.error);
	return convertValue(result.data, result.type);
}

std::unique_ptr<JsonValue> JsonParser::parseString(const std::string &str, JsonParserInfos *infos)
{
	JsonParserResult result = JsonParser_parseString(str.c_str(), infos);

	if (result.error)
		throw InvalidJsonStringException(result.error);
	return convertValue(result.data, result.type);
}