/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonBoolean.hpp
*/

#ifndef JSON_PARSER_JSONBOOLEAN_HPP
#define JSON_PARSER_JSONBOOLEAN_HPP


#include "JsonValue.hpp"

class JsonBoolean : public JsonValue {
private:
	bool	_value;

public:
	JsonBoolean(bool value);
	bool &value();
	void dump(unsigned int indent = 0) const override;
};


#endif //JSON_PARSER_JSONBOOLEAN_HPP
