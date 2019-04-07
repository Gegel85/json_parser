/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonArray.hpp
*/

#ifndef JSON_PARSER_JSONARRAY_HPP
#define JSON_PARSER_JSONARRAY_HPP


#include <vector>
#include <memory>
#include "JsonValue.hpp"

class JsonArray : public JsonValue {
private:
	std::vector<std::unique_ptr<JsonValue>>	_value;

public:
	JsonArray() = default;
	JsonArray(JsonParserList &elem);
	JsonArray(JsonParserArray &elem);
	std::unique_ptr<JsonValue> &operator[](int);
	std::vector<std::unique_ptr<JsonValue>> &value();
	void dump(unsigned int indent = 0) const override;
};


#endif //JSON_PARSER_JSONARRAY_HPP
