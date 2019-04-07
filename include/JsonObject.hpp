/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonObject.hpp
*/

#ifndef JSON_PARSER_JSONOBJECT_HPP
#define JSON_PARSER_JSONOBJECT_HPP

#include <map>
#include <string>
#include <memory>
#include "JsonValue.hpp"

class JsonObject : public JsonValue {
private:
	std::map<std::string, std::unique_ptr<JsonValue>>	_value;

public:
	JsonObject() = default;
	JsonObject(JsonParserObj &elem);
	std::unique_ptr<JsonValue> &operator[](const std::string &);
	std::map<std::string, std::unique_ptr<JsonValue>> &value();
	void dump(unsigned int indent = 0) const override;
};


#endif //JSON_PARSER_JSONOBJECT_HPP
