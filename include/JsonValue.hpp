/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonValue.hpp
*/

#ifndef JSON_PARSER_JSONVALUE_HPP
#define JSON_PARSER_JSONVALUE_HPP


extern "C" {
#include <JsonParser.h>
};

class JsonValue {
public:
	virtual void dump(unsigned int indent = 0) const = 0;

	template <typename type>
	bool is() {
		type *result = dynamic_cast<type *>(this);

		return result != nullptr;
	};

	template <typename type>
	type &to() {
		return dynamic_cast<type &>(*this);
	};
};


#endif //JSON_PARSER_JSONVALUE_HPP
