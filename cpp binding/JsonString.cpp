/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonString.cpp
*/

#include <iostream>
#include "../include/JsonString.hpp"

JsonString::JsonString(const std::string &value) : _value(value)
{
}

std::string &JsonString::value()
{
	return this->_value;
}

void JsonString::dump(unsigned int __attribute__((unused)) indent) const
{
	std::cout << "\"" << this->_value << "\"" << std::endl;
}
