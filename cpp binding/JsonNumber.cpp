/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonNumber.cpp
*/

#include <iostream>
#include "../include/JsonNumber.hpp"

JsonNumber::JsonNumber(double value) : _value(value)
{
}

double &JsonNumber::value()
{
	return this->_value;
}

void JsonNumber::dump(unsigned int __attribute__((unused)) indent) const
{
	std::cout << this->_value << std::endl;
}