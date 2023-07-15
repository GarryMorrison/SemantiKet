#pragma once

#include "../../SemantiKet.h"
#include <string>
#include <iostream>
#include <fstream>

std::string file_to_string(const std::string& filename);
void string_to_file(const std::string& filename, const std::string& str);

