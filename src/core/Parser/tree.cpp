#pragma once

// Author: Garry Morrison
// Added: 2023-9-23
// Updated: 2023-9-23

#include <map>
#include "tree.h"

namespace SKet {

    void Tree::print(int level)
    {
        for (int i = 0; i < level; i++)
        {
            std::cout << "  ";
        }
        if (nkids == 0)
        {
            std::cout << id << "    " << tok.text << " (" << tok.type_to_string() << "): line " << tok.line << ", column " << tok.col << "\n";
        }
        else
        {
            std::cout << id << "    " << sym << " (" << rule << "): children: " << nkids << "\n";
            for (Tree* tree : kids)
            {
                if (tree)
                {
                    tree->print(level + 1);
                }
            }
        }
    }

    void Tree::save_graph(const std::string& filename)
    {
        std::ofstream output_file(filename);

        if (output_file.is_open())
        {
            output_file << "digraph {\n";
            output_graph(output_file);
            output_file << "}\n";
            output_file.close();
        }
        else
        {
            std::cerr << "save graph failed to open file: " << filename << "\n";
        }
    }

    void Tree::output_graph(std::ofstream& out)
    {
        if (nkids == 0)
        {
            output_leaf(out);
            return;
        }
        output_branch(out);
        for (Tree* child : kids)
        {
            if (child)
            {
                out << "N" << id << " -> N" << child->id << ";\n";
                child->output_graph(out);
            }
        }
    }

    void Tree::output_leaf(std::ofstream& out)
    {
        std::string s = tok.type_to_string();
        output_branch(out);
        out << "N" << id << " [shape=box style=dotted label=\" " << s << " \\n ";
        out << "text = " << tok.text << " \\l line = " << tok.line << " \\l column = " << tok.col << " \\l\"];\n";
    }

    void Tree::output_branch(std::ofstream& out)
    {
        out << "N" << id << " [shape=box label=\"" << pretty_print_name() << "\"]; \n";
    }

    std::string Tree::pretty_print_name()
    {
        if (tok.text.empty())
        {
            return sym + "#" + std::to_string(rule);
        }
        else
        {
            return tok.text + ":" + tok.type_to_string();
        }
    }

    Tree::Tree(const std::string& s, int r, Tree* t1)
    {
        id = serial.get_id();
        sym = s;
        rule = r;
        nkids = 0;
        if (t1)
        {
            kids.push_back(t1);
            nkids++;
        }
    }

    Tree::Tree(const std::string& s, int r, Tree* t1, Tree* t2)
    {
        id = serial.get_id();
        sym = s;
        rule = r;
        nkids = 0;
        if (t1)
        {
            kids.push_back(t1);
            nkids++;
        }
        if (t2)
        {
            kids.push_back(t2);
            nkids++;
        }
    }

    Tree::Tree(const std::string& s, int r, Tree* t1, Tree* t2, Tree* t3)
    {
        id = serial.get_id();
        sym = s;
        rule = r;
        nkids = 0;
        if (t1)
        {
            kids.push_back(t1);
            nkids++;
        }
        if (t2)
        {
            kids.push_back(t2);
            nkids++;
        }
        if (t3)
        {
            kids.push_back(t3);
            nkids++;
        }
    }

    Tree::Tree(const std::string& s, int r, Tree* t1, Tree* t2, Tree* t3, Tree* t4)
    {
        id = serial.get_id();
        sym = s;
        rule = r;
        nkids = 0;
        if (t1)
        {
            kids.push_back(t1);
            nkids++;
        }
        if (t2)
        {
            kids.push_back(t2);
            nkids++;
        }
        if (t3)
        {
            kids.push_back(t3);
            nkids++;
        }
        if (t4)
        {
            kids.push_back(t4);
            nkids++;
        }
    }

};
