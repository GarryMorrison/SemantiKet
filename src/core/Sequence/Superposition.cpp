// Author: Garry Morrison
// Added: 2023-9-20
// Updated: 2023-9-20

#include "Superposition.h"
#include <algorithm>
#include <random>
#include <iterator>

extern std::mt19937 rng;

/*
	bool is_transpose = false;
	size_t max_index = 0;
	std::vector<size_t> sort_order;
	label_type ket_label_type;
	std::map<size_t, double> coeffs;

	std::map<size_t, std::string> pos2str_label;
	std::map<std::string, size_t> str_label2pos;

	std::map<size_t, double> pos2float_label;
	std::map<double, size_t> float_label2pos;
*/

Superposition Superposition::copy()
{
	Superposition sp2;
	sp2.is_transpose = is_transpose;
	sp2.max_index = max_index;
	std::copy(sort_order.begin(), sort_order.end(), std::back_inserter(sp2.sort_order));
	sp2.ket_label_type = ket_label_type;
	sp2.coeffs = coeffs;

	sp2.pos2str_label = pos2str_label;
	sp2.str_label2pos = str_label2pos;

	sp2.pos2float_label = pos2float_label;
	sp2.float_label2pos = float_label2pos;

	return sp2;
}

void Superposition::clear()
{
	is_transpose = false;
	max_index = 0;
	sort_order.clear();
	ket_label_type = STRING;
	coeffs.clear();
	pos2str_label.clear();
	str_label2pos.clear();
	pos2float_label.clear();
	float_label2pos.clear();
}

void Superposition::transpose()
{
	is_transpose = !is_transpose;
}

std::string Superposition::to_string()
{
	if (sort_order.size() == 0)
	{
		return "|>";
	}

	std::string s;
	bool first_pass = true;
	for (size_t idx : sort_order)
	{
		double coeff = coeffs[idx];  // Assume maps are well maintained, so no key access errors
		std::string label = pos2str_label[idx];  // Assume maps are well maintained, so no key access errors
		std::string coeff_str;
		if (coeff == 1)
		{
			coeff_str = "";
		}
		else
		{
			// coeff_str = std::to_string(coeff);
			coeff_str = float_to_str(coeff, 6);
		}
		if (!is_transpose)
		{
			if (!first_pass && coeff > 0)
			{
				if (coeff != 1)
				{
					s.append(" + ");
				}
				else
				{
					s.append(" +");
				}
			}
			else
			{
					s.append(" ");
			}
			s.append(coeff_str);
			s.append(" |");
			s.append(label);
			s.append(">");
		}
		else
		{
			if (!first_pass)
			{
				s.append(" + ");
			}
			s.append("<");
			s.append(label);
			s.append("| ");
			s.append(coeff_str);
		}
		first_pass = false;
	}
	return s;
}

std::string Superposition::human_string()  // TODO!
{
	return ""; // dummy for now
}

bool Superposition::do_you_know()
{
	return sort_order.size() != 0;
}

bool Superposition::is_ket()
{
	return sort_order.size() <= 1;
}

bool Superposition::is_sp()
{
	return sort_order.size() > 1;
}

size_t Superposition::how_many()
{
	return sort_order.size();
}

double Superposition::measure_currency()
{
	double F = 0;
	for (size_t idx : sort_order)
	{
		F += coeffs[idx]; // assume map is well constructed and we don't get a key error!
	}
	return F;
}

double Superposition::read_coeff(std::string s1)
{
	if (str_label2pos.find(s1) == str_label2pos.end())
	{
		return 0;
	}
	size_t idx = str_label2pos[s1];
	return coeffs[idx];
}

void Superposition::add(std::string s1)  // still incomplete ....
{
	if (str_label2pos.find(s1) != str_label2pos.end())
	{
		size_t idx = str_label2pos[s1];
		coeffs[idx] += 1;
	}
	else
	{
		size_t idx = max_index;
		max_index++;
		sort_order.push_back(idx);
		ket_label_type = STRING;
		pos2str_label[idx] = s1;
		str_label2pos[s1] = idx;
		coeffs[idx] = 1;
	}
}

void Superposition::add(std::string s1, double F1)  // still incomplete ....
{
	if (str_label2pos.find(s1) != str_label2pos.end())
	{
		size_t idx = str_label2pos[s1];
		coeffs[idx] += F1;
	}
	else
	{
		size_t idx = max_index;
		max_index++;
		sort_order.push_back(idx);
		ket_label_type = STRING;
		pos2str_label[idx] = s1;
		str_label2pos[s1] = idx;
		coeffs[idx] = F1;
	}
}

void Superposition::mult(double F1)
{
	for (size_t idx : sort_order)
	{
		coeffs[idx] *= F1;
	}
}

void Superposition::clean()
{
	for (size_t idx : sort_order)
	{
		coeffs[idx] = 1;
	}
}

void Superposition::drop()
{
	std::vector<size_t> sort_order2;
	for (size_t idx : sort_order)
	{
		double coeff = coeffs[idx];
		if (coeff > 0)
		{
			sort_order2.push_back(idx);
		}
		else
		{
			coeffs.erase(idx);
			std::string label = pos2str_label[idx]; // handle float labels later!
			pos2str_label.erase(idx);
			str_label2pos.erase(label);
		}
	}
	sort_order = std::move(sort_order2);
}

void Superposition::drop_below(double t)
{
	std::vector<size_t> sort_order2;
	for (size_t idx : sort_order)
	{
		double coeff = coeffs[idx];
		if (coeff >= t)
		{
			sort_order2.push_back(idx);
		}
		else
		{
			coeffs.erase(idx);
			std::string label = pos2str_label[idx]; // handle float labels later!
			pos2str_label.erase(idx);
			str_label2pos.erase(label);
		}
	}
	sort_order = std::move(sort_order2);
}

void Superposition::drop_above(double t)
{
	std::vector<size_t> sort_order2;
	for (size_t idx : sort_order)
	{
		double coeff = coeffs[idx];
		if (coeff <= t)
		{
			sort_order2.push_back(idx);
		}
		else
		{
			coeffs.erase(idx);
			std::string label = pos2str_label[idx]; // handle float labels later!
			pos2str_label.erase(idx);
			str_label2pos.erase(label);
		}
	}
	sort_order = std::move(sort_order2);
}

void Superposition::pick_elt()
{
	std::vector<size_t> sort_order2;
	std::uniform_int_distribution<size_t> distr(0, sort_order.size() - 1);
	size_t idx2 = distr(rng);
	sort_order2.push_back(idx2);
	for (size_t idx : sort_order)  // use .clear() instead?
	{
		if (idx != idx2)
		{
			coeffs.erase(idx);
			std::string label = pos2str_label[idx]; // handle float labels later!
			pos2str_label.erase(idx);
			str_label2pos.erase(label);
		}
	}
	sort_order = std::move(sort_order2);
}

void Superposition::weighted_pick_elt()
{
	double sum = 0;
	std::vector<size_t> sort_order2;
	for (size_t idx : sort_order)
	{
		double coeff = coeffs[idx];
		if (coeff > 0)
		{
			sum += coeff;
			sort_order2.push_back(idx);
		}
	}
	if (sum == 0)
	{
		clear(); // create the empty ket
		return;
	}
	std::uniform_real_distribution<double> distr(0, sum);
	double r = distr(rng);
	double upto = 0;
	for (size_t idx : sort_order2)
	{
		double w = coeffs[idx];
		if (upto + w > r)
		{
			// return idx as the new ket. TODO!
			std::string label = pos2str_label[idx];
			clear(); // reset to the empty ket
			max_index = 1; // build the new ket
			sort_order.push_back(0);
			coeffs[0] = w;
			pos2str_label[0] = label;
			str_label2pos[label] = 0;
			return;
		}
		upto += w;
	}
	clear(); // create the empty ket
	return;
}

void Superposition::pick(size_t n)
{
	size_t n2 = std::min(n, sort_order.size());
	std::vector<size_t> sort_order2;
	std::shuffle(sort_order.begin(), sort_order.end(), rng);
	for (size_t i = 0; i < n2; i++)
	{
		size_t idx = sort_order[i];
		sort_order2.push_back(idx);
	}
	for (size_t i = n2; i < sort_order.size(); i++)
	{
		size_t idx = sort_order[i];
		coeffs.erase(idx);
		std::string label = pos2str_label[idx]; // handle float labels later!
		pos2str_label.erase(idx);
		str_label2pos.erase(label);
	}
	sort_order = std::move(sort_order2);
}

void Superposition::normalize1()
{
	double sum = 0;
	for (size_t idx : sort_order)
	{
		sum += coeffs[idx];
	}
	if (sum == 0)  // is this the best thing to do if sum == 0?
	{
		return;
	}
	for (size_t idx : sort_order)
	{
		coeffs[idx] /= sum;
	}
}

void Superposition::normalize1(double t)
{
	double sum = 0;
	for (size_t idx : sort_order)
	{
		sum += coeffs[idx];
	}
	if (sum == 0)  // is this the best thing to do if sum == 0?
	{
		return;
	}
	for (size_t idx : sort_order)
	{
		coeffs[idx] /= sum;
		coeffs[idx] *= t;
	}
}


void Superposition::normalize2()
{
	double sum = 0;
	for (size_t idx : sort_order)
	{
		sum += coeffs[idx] * coeffs[idx];
	}
	if (sum == 0)  // is this the best thing to do if sum == 0?
	{
		return;
	}
	for (size_t idx : sort_order)
	{
		coeffs[idx] /= sum;
	}
}

void Superposition::rescale()
{
	double max = 0;
	for (size_t idx : sort_order)
	{
		max = std::max(max, coeffs[idx]);
	}
	if (max == 0)
	{
		return;
	}
	for (size_t idx : sort_order)
	{
		coeffs[idx] /= max;
	}
}

void Superposition::rescale(double t)
{
	double max = 0;
	for (size_t idx : sort_order)
	{
		max = std::max(max, coeffs[idx]);
	}
	if (max == 0)
	{
		return;
	}
	for (size_t idx : sort_order)
	{
		coeffs[idx] /= max;
		coeffs[idx] *= t;
	}
}

/*
void Superposition::coeff_sort() {
	std::sort(sort_order.begin(), sort_order.end(), [this](ulong a, ulong b) { return this->sp[a] > this->sp[b]; });
}
*/

void Superposition::coeff_sort()
{
	std::sort(sort_order.begin(), sort_order.end(), [this](size_t a, size_t b) { return this->coeffs[a] > this->coeffs[b]; });
}

void Superposition::ket_sort()
{
	std::sort(sort_order.begin(), sort_order.end(), [this](size_t a, size_t b) { return this->pos2str_label[a] < this->pos2str_label[b]; });
}

void Superposition::reverse()
{
	std::reverse(sort_order.begin(), sort_order.end());
}

void Superposition::shuffle()
{
	std::shuffle(sort_order.begin(), sort_order.end(), rng);
}

/*
	bool is_transpose = false;
	size_t max_index = 0;
	std::vector<size_t> sort_order;
	label_type ket_label_type;
	std::map<size_t, double> coeffs;

	std::map<size_t, std::string> pos2str_label;
	std::map<std::string, size_t> str_label2pos;

	std::map<size_t, double> pos2float_label;
	std::map<double, size_t> float_label2pos;
*/

void Superposition::merge()
{
	double coeff2 = 1;
	std::string label2;
	for (size_t idx : sort_order)
	{
		coeff2 *= coeffs[idx];
		label2.append(pos2str_label[idx]);
	}
	sort_order.clear(); // erase current data
	coeffs.clear();
	pos2str_label.clear();
	str_label2pos.clear();
	pos2float_label.clear();
	float_label2pos.clear();

	max_index = 1; // populate new data
	sort_order.push_back(0);
	coeffs[0] = coeff2;
	pos2str_label[0] = label2;
	str_label2pos[label2] = 0;
}

void Superposition::merge(std::string s1)
{
	double coeff2 = 1;
	std::string label2;
	bool first_pass = true;
	for (size_t idx : sort_order)
	{
		coeff2 *= coeffs[idx];
		if (!first_pass)
		{
			label2.append(s1);
		}
		label2.append(pos2str_label[idx]);
		first_pass = false;
	}
	sort_order.clear(); // erase current data
	coeffs.clear();
	pos2str_label.clear();
	str_label2pos.clear();
	pos2float_label.clear();
	float_label2pos.clear();

	max_index = 1; // populate new data
	sort_order.push_back(0);
	coeffs[0] = coeff2;
	pos2str_label[0] = label2;
	str_label2pos[label2] = 0;
}

Superposition Superposition::split()
{
	Superposition sp2;
	for (size_t idx : sort_order)
	{
		double coeff = coeffs[idx];
		std::string label = pos2str_label[idx];
		for (char c : label)
		{
			std::string s(1, c);
			sp2.add(s, coeff);
		}
	}
	return sp2;
}

Superposition Superposition::split(const std::string &s1)
{
	Superposition sp2;
	for (size_t idx : sort_order)
	{
		double coeff = coeffs[idx];
		std::string label = pos2str_label[idx];
		std::vector<std::string> svec = split_str(label, s1);
		for (std::string &s : svec)
		{
			sp2.add(s, coeff);
		}
	}
	return sp2;
}

Superposition Superposition::range(double F1, double F2)
{
	Superposition sp2;
	if (F2 < F1)
	{
		return sp2;
	}
	int i1 = static_cast<long long int>(F1); // convert to ints for now. TODO: full float version!
	int i2 = static_cast<long long int>(F2);
	for (int i = i1; i <= i2; i++)
	{
		std::string label = std::to_string(i); // later use float labels here!
		size_t idx2 = sp2.max_index;
		sp2.max_index++;
		sp2.sort_order.push_back(idx2);
		sp2.coeffs[idx2] = 1;
		sp2.pos2str_label[idx2] = label;
		sp2.str_label2pos[label] = idx2;
	}
	return sp2;
}

Superposition Superposition::range(double F1, double F2, double F3)
{
	Superposition sp2;
	if (F3 == 0) // stop empty steps from being an infinite loop
	{
		return sp2;
	}
	if ((F1 > F2 && F3 > 0) || (F1 < F2 && F3 < 0))
	{
			return sp2;
	}
	int i1 = static_cast<long long int>(F1); // convert to ints for now. TODO: full float version!
	int i2 = static_cast<long long int>(F2);
	int i3 = static_cast<long long int>(F3);
	if (i1 <= i2 && i3 > 0)
	{
		for (int i = i1; i <= i2; i += i3)
		{
			std::string label = std::to_string(i); // later use float labels here!
			size_t idx2 = sp2.max_index;
			sp2.max_index++;
			sp2.sort_order.push_back(idx2);
			sp2.coeffs[idx2] = 1;
			sp2.pos2str_label[idx2] = label;
			sp2.str_label2pos[label] = idx2;
		}
	}
	else if (i1 >= i2 && i3 < 0)
	{
		for (int i = i1; i >= i2; i += i3)
		{
			std::string label = std::to_string(i); // later use float labels here!
			size_t idx2 = sp2.max_index;
			sp2.max_index++;
			sp2.sort_order.push_back(idx2);
			sp2.coeffs[idx2] = 1;
			sp2.pos2str_label[idx2] = label;
			sp2.str_label2pos[label] = idx2;
		}
	}
	return sp2;
}

double Superposition::cread(double F1) // used in cfor loops // later handle -ve indices too? eg, -1 |=> sort_order.size().
{
	size_t i = static_cast<size_t>(F1);
	if (i == 0)
	{
		// symtab.error("value", "cread", "index starts at 1 not 0"); // maybe make error messages global, not defined inside operators?
		// symtab.error("cread", 12345);  // 12345 maps to: type of "value error", and message of "index starts at 1 not 0".
		return 0;
	}
	if (i < 1 || i > sort_order.size())
	{
		// symtab.error("value", "cread", "index is out of range"); // later return valid range? ie, 1 .. sort_order.size()? Using our format string?
		return 0;
	}
	size_t idx = sort_order[i - 1];
	return coeffs[idx];
}

Superposition Superposition::lread(double F1) // used in lfor loops
{
	Superposition sp;
	size_t i = static_cast<size_t>(F1);
	if (i == 0)
	{
		// symtab.error("value", "lread", "index starts at 1 not 0");
		return sp;
	}
	if (i < 1 || i > sort_order.size())
	{
		// symtab.error("value", "lread", "index is out of range");
		return sp;
	}
	size_t idx = sort_order[i - 1];
	std::string label = pos2str_label[idx];
	sp.add(label);
	return sp;
}

Superposition Superposition::read(double F1) // used in for loops
{
	Superposition sp;
	size_t i = static_cast<size_t>(F1);
	if (i == 0)
	{
		// symtab.error("value", "read", "index starts at 1 not 0");
		return sp;
	}
	if (i < 1 || i > sort_order.size())
	{
		// symtab.error("value", "read", "index is out of range");
		return sp;
	}
	size_t idx = sort_order[i - 1];
	double coeff = coeffs[idx];
	std::string label = pos2str_label[idx];
	sp.add(label, coeff);
	return sp;
}
