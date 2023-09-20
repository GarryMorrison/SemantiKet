#pragma once

#include "../../SemantiKet.h"
#include <string>
#include <iostream>
#include <fstream>

const double EPSILON = 0.0001;

std::string file_to_string(const std::string& filename, bool verbose = true);
void string_to_file(const std::string& filename, const std::string& str);
bool test_files_equal(const std::string& filename1, const std::string& filename2);
bool create_directory(const std::string& path);
bool delete_file(const std::string& filename, bool verbose = true);
std::string remove_extension(const std::string& filename, const std::string& ext);
bool has_extension(const std::string& filename);

std::string getCurrentDateTimeString(const std::string& date_sep = "-", const std::string& date_time_sep = " ", const std::string& time_sep = ":");

std::string indent(int width);
std::string pad_digits(int number, int width);
std::string pad_str_right(std::string s, int width);
std::string pad_str(std::string s, std::string delim, int width, bool left = true);

std::vector<std::string> split_str(const std::string& s1, const std::string& delimiter);

bool double_eq(double F1, double F2);
int ipower(int a, int n);
std::string float_to_str(double f, unsigned int digits); // We make no attempt to round the final digit. We assume float is not in exponentation notation too!
std::string bool_to_str(bool B1);

std::string format_string(std::string s, std::vector<std::string>& params);
std::string format_string(std::string s, std::string p1);
std::string format_string(std::string s, std::string p1, std::string p2);
std::string format_string(std::string s, std::string p1, std::string p2, std::string p3);
std::string format_string(std::string s, std::string p1, std::string p2, std::string p3, std::string p4);
std::string format_string(std::string s, std::string p1, std::string p2, std::string p3, std::string p4, std::string p5);

