#pragma once

// Author: Garry Morrison
// Added: 2023-9-23
// Updated: 2023-9-23

#include <map>
#include "../../SemantiKet.h"
// #include "Serial.h"

// #include "token.h"
// #include "parser.tab.h"
extern Serial serial;
// class SKet::yyTOKEN;


namespace SKet {

    class yyTOKEN;

    class Tree
    {
    public:
        int id;  // type int or size_t?
        std::string sym;
        int rule = 0;
        size_t nkids;
        yyTOKEN tok;
        std::vector<Tree*> kids;

        Tree(const std::string& s) { id = serial.get_id(); sym = s; nkids = 0; }
        Tree(const std::string& s, int r, yyTOKEN t) { id = serial.get_id(); sym = s; rule = r; tok = t; nkids = 0; }
        Tree(const std::string& s, int r, std::vector<Tree*> t) { id = serial.get_id(); sym = s; rule = r; nkids = t.size(); kids = t; }

        Tree(const std::string& s, int r) { id = serial.get_id(); sym = s; rule = r; nkids = 0; }
        Tree(const std::string& s, int r, Tree* t1);
        Tree(const std::string& s, int r, Tree* t1, Tree* t2);  // We have to do this because C++ doesn't have clean variadic functions!
        Tree(const std::string& s, int r, Tree* t1, Tree* t2, Tree* t3);
        Tree(const std::string& s, int r, Tree* t1, Tree* t2, Tree* t3, Tree* t4);

        void print(int level);
        void print() { print(0); }
        void save_graph(const std::string& filename);
        void output_graph(std::ofstream& out);
        void output_leaf(std::ofstream& out);
        void output_branch(std::ofstream& out);
        std::string pretty_print_name();

    private:

    };

};