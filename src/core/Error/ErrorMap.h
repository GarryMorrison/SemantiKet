#pragma once

// Author: Garry Morrison
// Added: 2023-9-22
// Updated: 2023-9-22

#include "../../SemantiKet.h"
#include <map>

class ErrorMap
{
private:
	std::map<size_t, std::string> error_type_map;
	std::map<size_t, std::string> error_message_map;
	std::map<size_t, std::string> error_description_map;

	std::map<size_t, std::string> warning_type_map;
	std::map<size_t, std::string> warning_message_map;
	std::map<size_t, std::string> warning_description_map;

public:
	void populate_error_maps();
	void populate_warning_maps();

	std::string get_error_type(size_t code);
	std::string get_error_message(size_t code);
	std::string get_error_description(size_t code);

	std::string get_warning_type(size_t code);
	std::string get_warning_message(size_t code);
	std::string get_warning_description(size_t code);
};