#include <iostream>
#include "../include/JsonArray.hpp"
#include "../include/JsonParser.hpp"

JsonArray::JsonArray(JsonParserList &elem)
{
	for (JsonParserList *list = &elem; list && (list->data || list->type == JsonParserNullType); list = list->next)
		this->_value.push_back(
			JsonParser::convertValue(
				list->data,
				list->type
			)
		);
}

JsonArray::JsonArray(JsonParserArray &elem)
{
	for (int i = 0; i < elem.length; i++)
		this->_value.push_back(
			JsonParser::convertValue(
				JsonParserArray_getElement(&elem, i),
				elem.type
			)
		);
}

std::unique_ptr<JsonValue> &JsonArray::operator[](int id)
{
	return this->_value.at(id);
}

std::vector<std::unique_ptr<JsonValue>> &JsonArray::value()
{
	return this->_value;
}

void JsonArray::dump(unsigned int indent) const
{
	std::string str;

	str.reserve(indent);
	for (unsigned i = 0; i < indent; i++)
		str += "\t";
	std::cout << "[" << std::endl;
	for (const std::unique_ptr<JsonValue> &val : this->_value) {
		std::cout << str << '\t';
		val->dump(indent + 1);
	}
	std::cout << str << "]" << std::endl;
}