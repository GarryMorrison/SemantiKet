// Author: Garry Morrison
// Added: 2023-9-22
// Updated: 2023-9-22

#include "ErrorMap.h"

void ErrorMap::populate_error_maps()  // Need to assign error code values later! 0 for now.
{
	error_type_map[0] = "type";
	error_message_map[0] = "found superposition, expecting ket";
	error_description_map[0] = "";

	error_type_map[0] = "type";
	error_message_map[0] = "found sequence, expecting superposition";
	error_description_map[0] = "";

	error_type_map[0] = "value";
	error_message_map[0] = "index starts at 1 not 0";
	error_description_map[0] = "";

	error_type_map[0] = "value";
	error_message_map[0] = "index out of range";
	error_description_map[0] = "";
}

void ErrorMap::populate_warning_maps()
{

}


std::string ErrorMap::get_error_type(size_t code)
{
	if (error_type_map.find(code) == error_type_map.end())
	{
		return "UNKNOWN errror code: " + std::to_string(code);
	}
	return error_type_map[code];
}

std::string ErrorMap::get_error_message(size_t code)
{
	if (error_message_map.find(code) == error_message_map.end())
	{
		return "UNKNOWN errror code: " + std::to_string(code);
	}
	return error_message_map[code];
}

std::string ErrorMap::get_error_description(size_t code)
{
	if (error_description_map.find(code) == error_description_map.end())
	{
		return "UNKNOWN errror code: " + std::to_string(code);
	}
	return error_description_map[code];
}


std::string ErrorMap::get_warning_type(size_t code)
{
	if (warning_type_map.find(code) == warning_type_map.end())
	{
		return "UNKNOWN warning code: " + std::to_string(code);
	}
	return warning_type_map[code];
}

std::string ErrorMap::get_warning_message(size_t code)
{
	if (warning_message_map.find(code) == warning_message_map.end())
	{
		return "UNKNOWN warning code: " + std::to_string(code);
	}
	return warning_message_map[code];
}

std::string ErrorMap::get_warning_description(size_t code)
{
	if (warning_description_map.find(code) == warning_description_map.end())
	{
		return "UNKNOWN warning code: " + std::to_string(code);
	}
	return warning_description_map[code];
}

