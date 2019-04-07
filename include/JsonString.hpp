/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonString.hpp
*/

#ifndef JSON_PARSER_JSONSTRING_HPP
#define JSON_PARSER_JSONSTRING_HPP


#include <string>
#include "JsonValue.hpp"

class JsonString : public JsonValue {
private:
	std::string	_value;

public:
	JsonString(const std::string &value);
	std::string &value();
	void dump(unsigned int indent = 0) const override;
};


#endif //JSON_PARSER_JSONSTRING_HPP
