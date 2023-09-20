#pragma once

// Author: Garry Morrison
// Added: 2023-9-20
// Updated: 2023-9-20

#include "../../SemantiKet.h"

#include <vector>
#include <map>


enum label_type { STRING, DOUBLE, SIZET };


class Superposition
{
public:
	bool is_transpose = false;
	size_t max_index = 0;
	std::vector<size_t> sort_order;
	label_type ket_label_type;
	std::map<size_t, double> coeffs;

	std::map<size_t, std::string> pos2str_label;
	std::map<std::string, size_t> str_label2pos;

	std::map<size_t, double> pos2float_label; // not currently implemented!
	std::map<double, size_t> float_label2pos;

	Superposition copy();
	void clear();
	void transpose();
	std::string to_string();
	std::string human_string();
	bool do_you_know();
	bool is_ket();
	bool is_sp();
	size_t how_many();
	double measure_currency();
	double read_coeff(std::string s1);
	void add(std::string s1);
	void add(std::string s1, double coeff);
	void mult(double F1);
	void clean();
	void drop();
	void drop_below(double t);
	void drop_above(double t);
	void pick_elt();
	void weighted_pick_elt();
	void pick(size_t n);
	void normalize1();
	void normalize1(double t);
	void normalize2();
	// void normalize2(double t);
	void rescale();
	void rescale(double t);

	void coeff_sort();
	void ket_sort(); // later swap in natural sort!
	void reverse();
	void shuffle();

	void merge();
	void merge(std::string s1);

	Superposition split();
	Superposition split(const std::string &s1);

	Superposition range(double F1, double F2);
	Superposition range(double F1, double F2, double F3);
};