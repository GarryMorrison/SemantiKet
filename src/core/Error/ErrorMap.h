#pragma once

// Author: Garry Morrison
// Added: 2023-9-22
// Updated: 2023-9-22

// #include "../../SemantiKet.h"
#include <map>
#include <string>

enum class ErrorType { E0, E1, E2, E3 };
enum class WarningType { W0, W1 };


class ErrorMap
{
private:
	std::map<ErrorType, std::string> ErrorName; // private or public?
	std::map<WarningType, std::string> WarningName;

	std::map<ErrorType, std::string> error_type_map;
	std::map<ErrorType, std::string> error_message_map;
	std::map<ErrorType, std::string> error_description_map;

	std::map<WarningType, std::string> warning_type_map;
	std::map<WarningType, std::string> warning_message_map;
	std::map<WarningType, std::string> warning_description_map;

public:
	void populate_error_maps();
	void populate_warning_maps();

	std::string get_error_type(ErrorType code);
	std::string get_error_message(ErrorType code);
	std::string get_error_description(ErrorType code);

	std::string get_warning_type(WarningType code);
	std::string get_warning_message(WarningType code);
	std::string get_warning_description(WarningType code);
};