/*
** EPITECH PROJECT, 2019
** json_parser
** File description:
** main.cpp
*/

#include <memory>
#include <JsonParser.hpp>

int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <file.json> <key>" << std::endl;
		return EXIT_FAILURE;
	}

	try {
		std::unique_ptr <JsonValue> value = JsonParser::parseFile(argv[1]);

		value->dump();
		if (!value->is<JsonObject>()) {
			std::cerr << "An object is expected in the file" << std::endl;
			return EXIT_FAILURE;
		}

		JsonObject &obj = value->to<JsonObject>();

		if (obj[argv[2]])
			obj[argv[2]]->dump();
		else
			std::cout << "The key '" << argv[2] << "' wasn't found" << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}