/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonNull.hpp
*/

#ifndef JSON_PARSER_JSONNULL_HPP
#define JSON_PARSER_JSONNULL_HPP


#include <iostream>
#include "JsonValue.hpp"

class JsonNull : public JsonValue {
public:
	JsonNull() = default;
	void dump(unsigned int __attribute__((unused)) indent = 0) const override { std::cout << "null" << std::endl; }
};


#endif //JSON_PARSER_JSONNULL_HPP
