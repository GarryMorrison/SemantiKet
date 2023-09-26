// Author: Garry Morrison
// Added: 2023-9-22
// Updated: 2023-9-22

#include "ErrorMap.h"

void ErrorMap::populate_error_maps()  // Need to assign error code values later! 0 for now.
{
	ErrorName[ErrorType::E0] = "E0";  // Better codes and names later!
	ErrorName[ErrorType::E1] = "E1";
	ErrorName[ErrorType::E2] = "E2";
	ErrorName[ErrorType::E3] = "E3";

	error_type_map[ErrorType::E0] = "type";
	error_message_map[ErrorType::E0] = "found superposition, expecting ket";
	error_description_map[ErrorType::E0] = "";

	error_type_map[ErrorType::E1] = "type";
	error_message_map[ErrorType::E1] = "found sequence, expecting superposition";
	error_description_map[ErrorType::E1] = "";

	error_type_map[ErrorType::E2] = "value";
	error_message_map[ErrorType::E2] = "index starts at 1 not 0";
	error_description_map[ErrorType::E2] = "";

	error_type_map[ErrorType::E3] = "value";
	error_message_map[ErrorType::E3] = "index out of range";
	error_description_map[ErrorType::E3] = "";
}

void ErrorMap::populate_warning_maps()
{
	WarningName[WarningType::W0] = "W0";
}


std::string ErrorMap::get_error_type(ErrorType code)
{
	if (error_type_map.find(code) == error_type_map.end())
	{
		return "UNKNOWN errror code: " + ErrorName[code]; // ErrorName assumes code is defined!
	}
	return error_type_map[code];
}

std::string ErrorMap::get_error_message(ErrorType code)
{
	if (error_message_map.find(code) == error_message_map.end())
	{
		return "UNKNOWN errror code: " + ErrorName[code];
	}
	return error_message_map[code];
}

std::string ErrorMap::get_error_description(ErrorType code)
{
	if (error_description_map.find(code) == error_description_map.end())
	{
		return "UNKNOWN errror code: " + ErrorName[code];
	}
	return error_description_map[code];
}


std::string ErrorMap::get_warning_type(WarningType code)
{
	if (warning_type_map.find(code) == warning_type_map.end())
	{
		return "UNKNOWN warning code: " + WarningName[code];
	}
	return warning_type_map[code];
}

std::string ErrorMap::get_warning_message(WarningType code)
{
	if (warning_message_map.find(code) == warning_message_map.end())
	{
		return "UNKNOWN warning code: " + WarningName[code];
	}
	return warning_message_map[code];
}

std::string ErrorMap::get_warning_description(WarningType code)
{
	if (warning_description_map.find(code) == warning_description_map.end())
	{
		return "UNKNOWN warning code: " + WarningName[code];
	}
	return warning_description_map[code];
}

