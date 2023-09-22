﻿//
// Author: Garry Morrison
// Created: 2023/7/6
// Updated: 2023/7/6


// SemantiKet.cpp : Defines the entry point for the application.
//

#include <ctime>
#include <random>
#include <cstdlib>
#include <filesystem>
#include "SemantiKet.h"
// Define our serial global:
Serial serial;
 
// Define our parse tree:
SKet::Tree tree("the root");

// Define our parsing driver:
SKet::Driver driver(tree);

// Seed our random number generator:
std::mt19937 rng(time(nullptr));


int main(int argc, char* argv[])
{
	std::cout << "SemantiKet says hello ... " << std::endl;

	// Test format code:
	std::string our_format_string = "Format string: alpha = {}, beta = {}, gamma = {}\n";
	std::cout << format_string(our_format_string, "a1", "b1", "c1");

	// Test float_to_str:
	double f = 273.141592;
	std::cout << "Float to string: " << float_to_str(f, 4) << "\n";

	// Access command-line arguments
	for (int i = 0; i < argc; ++i) 
	{
		std::cout << "Argument " << i << ": " << argv[i] << std::endl;
	}

	std::cout << "Current path: " << std::filesystem::current_path() << std::endl;

	
	if (argc == 2)
	{
		std::cout << "----------------------------------";
		driver.parse_file(argv[1]);
		driver.tree.print();
		driver.tree.save_graph("syntax-tree.dot");
		std::system("dot -Tpng syntax-tree.dot > tree.png");  // Comment this out if you don't want it to auto generate an image of the syntax tree.
	}
	
	if (argc > 2)
	{
		std::string mode(argv[1]);
		std::string path(argv[2]);
		UnitTest utest;

		if (mode == "--test-parser-update-all")  // Update the parse results for all of our tests, over-writting previous parses.
		{
			utest.ParserUpdateAll(path);
		}
		else if (mode == "--test-parser-update-new")  // Update the parse results for tests that don't have parse results.
		{
			utest.ParserUpdateNew(path);
		}
		else if (mode == "--test-parser")  // Run parse tests on all the tests, and then compare with the previous parses (also, write output to screen and log file).
		{
			utest.ParserTest(path);
		}
		else if (mode == "--test-parser-update-all-with-png")  // Update the parse results for all of our tests, over-writting previous parses.
		{
			utest.ParserUpdateAll(path, true);
		}
		else if (mode == "--test-parser-update-new-with-png")  // Update the parse results for tests that don't have parse results.
		{
			utest.ParserUpdateNew(path, true);
		}
		else if (mode == "--test-parser-with-png")  // Run parse tests on all the tests, and then compare with the previous parses (also, write output to screen and log file).
		{
			utest.ParserTest(path, true);
		}
		else
		{
			std::cout << "\nInvalid option: " << mode << "\n";
			std::cout << "Valid options:\n";
			std::cout << "    --test-parser-update-all path-to-test-files/\n";
			std::cout << "    --test-parser-update-new path-to-test-files/\n";
			std::cout << "    --test-parser path-to-test-files/\n";
			std::cout << "    --test-parser-update-all-with-png path-to-test-files/\n";
			std::cout << "    --test-parser-update-new-with-png path-to-test-files/\n";
			std::cout << "    --test-parser-with-png path-to-test-files/\n\n";
			return 1;
		}
	}

	if (argc == 1)
	{

		// Test superposition class section:
		std::cout << "--------------------------------------------------\n";
		std::cout << "random number: " << rng() << "\n";
		std::cout << "bool: " << bool_to_str(true) << "\n";
		std::cout << "bool: " << bool_to_str(false) << "\n";
		double d1 = 1;
		std::cout << "double: " << std::to_string(d1) << "\n\n";

		Superposition sp;
		std::cout << "do you know: " << bool_to_str(sp.do_you_know()) << "\n";
		std::cout << "string: " << sp.to_string() << "\n\n";

		sp.add("a", 3);
		std::cout << "do you know: " << bool_to_str(sp.do_you_know()) << "\n";
		std::cout << "string: " << sp.to_string() << "\n";
		std::cout << "is ket: " << bool_to_str(sp.is_ket()) << "\n";
		std::cout << "is sp: " << bool_to_str(sp.is_sp()) << "\n\n";

		sp.add("b", 5);
		std::cout << "do you know: " << bool_to_str(sp.do_you_know()) << "\n";
		std::cout << "string: " << sp.to_string() << "\n";
		std::cout << "is ket: " << bool_to_str(sp.is_ket()) << "\n";
		std::cout << "is sp: " << bool_to_str(sp.is_sp()) << "\n\n";

		sp.add("c", -7);
		std::cout << "do you know: " << bool_to_str(sp.do_you_know()) << "\n";
		std::cout << "string: " << sp.to_string() << "\n";
		std::cout << "is ket: " << bool_to_str(sp.is_ket()) << "\n";
		std::cout << "is sp: " << bool_to_str(sp.is_sp()) << "\n";
		std::cout << "how many: " << std::to_string(sp.how_many()) << "\n";
		std::cout << "currency: " << std::to_string(sp.measure_currency()) << "\n\n";

		sp.transpose();
		std::cout << "transpose string: " << sp.to_string() << "\n\n";

		sp.transpose();
		sp.mult(-1);
		std::cout << "mult -1 string: " << sp.to_string() << "\n";
		std::cout << "currency: " << std::to_string(sp.measure_currency()) << "\n\n";

		sp.mult(-3);
		std::cout << "mult -3 string: " << sp.to_string() << "\n";
		std::cout << "currency: " << std::to_string(sp.measure_currency()) << "\n\n";

		sp.reverse();
		std::cout << "reverse string: " << sp.to_string() << "\n";
		sp.transpose();
		std::cout << "reverse transpose string: " << sp.to_string() << "\n\n";

		sp.transpose();
		sp.add("b", 1000);
		sp.reverse();
		sp.add("d");
		sp.add("e");
		sp.add("e");
		std::cout << "string: " << sp.to_string() << "\n";
		std::cout << "how many: " << std::to_string(sp.how_many()) << "\n";
		std::cout << "currency: " << std::to_string(sp.measure_currency()) << "\n\n";

		Superposition sp2 = sp.copy();
		Superposition sp3 = sp.copy();
		Superposition sp4 = sp.copy();
		Superposition sp5 = sp.copy();
		Superposition sp6 = sp.copy();

		sp.shuffle();
		std::cout << "shuffled string: " << sp.to_string() << "\n";
		sp.shuffle();
		std::cout << "shuffled string: " << sp.to_string() << "\n";
		sp.shuffle();
		std::cout << "shuffled string: " << sp.to_string() << "\n";
		sp.shuffle();
		std::cout << "shuffled string: " << sp.to_string() << "\n\n";

		double F1 = sp.read_coeff("a");
		double F2 = sp.read_coeff("b");
		double F3 = sp.read_coeff("c");
		double F4 = sp.read_coeff("d");
		double F5 = sp.read_coeff("e");
		double F6 = sp.read_coeff("z");
		std::cout << "coeff a: " << std::to_string(F1) << "\n";
		std::cout << "coeff b: " << std::to_string(F2) << "\n";
		std::cout << "coeff c: " << std::to_string(F3) << "\n";
		std::cout << "coeff d: " << std::to_string(F4) << "\n";
		std::cout << "coeff e: " << std::to_string(F5) << "\n";
		std::cout << "coeff z: " << std::to_string(F6) << "\n\n";

		sp.clean();
		std::cout << "clean string: " << sp.to_string() << "\n";
		std::cout << "how many: " << std::to_string(sp.how_many()) << "\n";
		std::cout << "currency: " << std::to_string(sp.measure_currency()) << "\n\n";

		sp.normalize1(100);
		std::cout << "normalize1 string 100: " << sp.to_string() << "\n";
		std::cout << "how many: " << std::to_string(sp.how_many()) << "\n";
		std::cout << "currency: " << std::to_string(sp.measure_currency()) << "\n\n";

		sp.rescale(5);
		std::cout << "rescale string 5: " << sp.to_string() << "\n";
		std::cout << "how many: " << std::to_string(sp.how_many()) << "\n";
		std::cout << "currency: " << std::to_string(sp.measure_currency()) << "\n\n";

		std::cout << "sp2 string: " << sp2.to_string() << "\n\n";

		sp2.coeff_sort();
		std::cout << "coeff sorted sp2 string: " << sp2.to_string() << "\n";
		sp2.ket_sort();
		std::cout << "ket sorted sp2 string: " << sp2.to_string() << "\n\n";

		sp2.drop();
		std::cout << "dropped sp2 string: " << sp2.to_string() << "\n";
		sp2.drop_below(3);
		std::cout << "dropped below 3 sp2 string: " << sp2.to_string() << "\n";
		sp2.drop_above(10);
		std::cout << "dropped above 10 sp2 string: " << sp2.to_string() << "\n\n";


		std::cout << "sp3 string: " << sp3.to_string() << "\n";
		sp3.pick_elt();
		std::cout << "pick random elt from sp3 string: " << sp3.to_string() << "\n\n";

		std::cout << "sp4 string: " << sp4.to_string() << "\n";
		sp4.pick(3);
		std::cout << "pick 3 random elts from sp4 string: " << sp4.to_string() << "\n\n";

		std::cout << "sp4 string: " << sp4.to_string() << "\n";
		sp4.merge();
		std::cout << "sp4 merged string: " << sp4.to_string() << "\n\n";

		std::cout << "sp5 string: " << sp5.to_string() << "\n";
		sp5.merge(": ");
		std::cout << "sp5 merged string: " << sp5.to_string() << "\n\n";

		sp6.drop_above(20);
		std::cout << "sp6 string: " << sp6.to_string() << "\n";
		sp6.weighted_pick_elt();
		std::cout << "weighted pick random elt sp6 string: " << sp6.to_string() << "\n\n";

		sp6.clear();
		std::cout << "clear sp6 string: " << sp6.to_string() << "\n\n";

		Superposition sp7;
		sp7.add("alpha", 3);
		sp7.add("beta", 5);
		std::cout << "sp7 string: " << sp7.to_string() << "\n";
		Superposition sp8 = sp7.split();
		std::cout << "split sp7 string: " << sp8.to_string() << "\n\n";

		Superposition sp9;
		sp9.add("alpha: beta: gamma", 11);
		std::cout << "sp9 string: " << sp9.to_string() << "\n";
		Superposition sp10 = sp9.split(": ");
		std::cout << "split sp9 string: " << sp10.to_string() << "\n\n";

		Superposition sp11 = sp10.range(10, 1);
		Superposition sp12 = sp10.range(1, 10);
		std::cout << "sp11 string: " << sp11.to_string() << "\n";
		std::cout << "sp12 string: " << sp12.to_string() << "\n\n";

		Superposition sp13 = sp10.range(1, 10, 2);
		Superposition sp14 = sp10.range(10, 1, -3);
		std::cout << "sp13 string: " << sp13.to_string() << "\n";
		std::cout << "sp14 string: " << sp14.to_string() << "\n\n";

		sp14.mult(3.2);
		double F7 = sp14.cread(2);
		Superposition sp15 = sp14.lread(2);
		Superposition sp16 = sp14.read(2);
		std::cout << "sp: " << sp14.to_string() << "\n";
		std::cout << "cread[2] sp: " << std::to_string(F7) << "\n";
		std::cout << "lread[2] sp: " << sp15.to_string() << "\n";
		std::cout << "read[2] sp: " << sp16.to_string() << "\n";

	}

	return 0;
}
