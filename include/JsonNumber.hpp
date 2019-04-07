/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonNumber.hpp
*/

#ifndef JSON_PARSER_JSONNUMBER_HPP
#define JSON_PARSER_JSONNUMBER_HPP


#include "JsonValue.hpp"

class JsonNumber : public JsonValue {
private:
	double	_value;

public:
	JsonNumber(double value);
	double &value();
	void dump(unsigned int indent = 0) const override;
};


#endif //JSON_PARSER_JSONNUMBER_HPP
