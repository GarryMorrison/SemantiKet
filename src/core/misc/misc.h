#pragma once

#include "../../SemantiKet.h"
#include <string>
#include <iostream>
#include <fstream>

std::string file_to_string(const std::string& filename);
void string_to_file(const std::string& filename, const std::string& str);
bool test_files_equal(const std::string& filename1, const std::string& filename2);
bool create_directory(const std::string& path);
bool delete_file(const std::string& filename, bool verbose = true);
std::string remove_extension(const std::string& filename, const std::string& ext);

std::string getCurrentDateTimeString(const std::string& date_sep = "-", const std::string& date_time_sep = " ", const std::string& time_sep = ":");