/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonObject.cpp
*/

#include <iostream>
#include "../include/JsonObject.hpp"
#include "../include/JsonParser.hpp"

JsonObject::JsonObject(JsonParserObj &elem)
{
	for (JsonParserObj *list = &elem; list && (list->data || list->type == JsonParserNullType); list = list->next)
		this->_value[list->index] = JsonParser::convertValue(list->data, list->type);
}

std::unique_ptr<JsonValue> &JsonObject::operator[](const std::string &id)
{
	return this->_value[id];
}

std::map<std::string, std::unique_ptr<JsonValue>> &JsonObject::value()
{
	return this->_value;
}

void JsonObject::dump(unsigned int __attribute__((unused)) indent) const
{
	std::string str;

	str.reserve(indent);
	for (unsigned i = 0; i < indent; i++)
		str += "\t";
	std::cout << "{" << std::endl;
	for (const std::pair<const std::string, std::unique_ptr<JsonValue>> &val : this->_value) {
		std::cout << str << "\t\"" << val.first << "\": ";
		val.second->dump(indent + 1);
	}
	std::cout << str << "}" << std::endl;
}