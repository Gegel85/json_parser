/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** JsonParser.hpp
*/

#ifndef JSON_PARSER_JSONPARSER_HPP
#define JSON_PARSER_JSONPARSER_HPP


#include <memory>
#include "JsonArray.hpp"
#include "JsonBoolean.hpp"
#include "JsonNull.hpp"
#include "JsonNumber.hpp"
#include "JsonObject.hpp"
#include "JsonString.hpp"
#include "JsonValue.hpp"

class JsonParser {
public:
	class Exception : public std::exception {
	private:
		std::string _msg;

	public:
		explicit Exception(const std::string &msg) : _msg(msg) {};
		const char *what() const noexcept { return this->_msg.c_str(); };
	};

	class InvalidJsonFileException : public Exception {
	public:
		explicit InvalidJsonFileException(const std::string &msg) : Exception(msg) {};
	};

	class InvalidJsonStringException : public Exception {
	public:
		explicit InvalidJsonStringException(const std::string &msg) : Exception(msg) {};
	};

	class InvalidTypeException : public Exception {
	public:
		explicit InvalidTypeException(const std::string &msg) : Exception(msg) {};
	};

	static std::unique_ptr<JsonValue> convertValue(void *data, JsonParserTypes type);
	static std::unique_ptr<JsonValue> parseFile(const std::string &path, JsonParserInfos *infos = nullptr);
	static std::unique_ptr<JsonValue> parseString(const std::string &str, JsonParserInfos *infos = nullptr);
};


#endif //JSON_PARSER_JSONPARSER_HPP
