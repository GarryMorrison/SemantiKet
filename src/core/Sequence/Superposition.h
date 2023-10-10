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
	std::string human_string();  // not currently implemented!
	bool do_you_know();
	bool is_ket();
	bool is_sp();
	size_t how_many();
	double measure_currency();
	double read_coeff(const std::string& s1);
	double max_coeff();
	double min_coeff();
	void add(const std::string& s1);
	void add(const std::string& s1, double coeff);
	void add(Superposition& sp);
	Superposition tensor_product(Superposition& sp);
	Superposition tensor_product(const std::string& s1, Superposition& sp);
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
	void merge(const std::string& s1);

	Superposition split();
	Superposition split(const std::string &s1);

	Superposition range(double F1, double F2);
	Superposition range(double F1, double F2, double F3);

	double cread(double F1); // used in cfor loops
	Superposition lread(double F1); // used in lfor loops
	Superposition read(double F1); // used in for loops

	void erase(double F1);

	void push_value();
	void pop_value();
};