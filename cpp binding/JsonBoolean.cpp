#include <iostream>
#include "../include/JsonBoolean.hpp"


JsonBoolean::JsonBoolean(bool value) : _value(value)
{
}

bool &JsonBoolean::value()
{
	return this->_value;
}

void JsonBoolean::dump(unsigned int __attribute__((unused)) indent) const
{
	std::cout << (this->_value ? "true" : "false") << std::endl;
}