#include "misc.h"

std::string file_to_string(const std::string& filename)
{
    std::ifstream file_stream{filename};

    if (file_stream.fail())
    {
        // Error opening file.
        std::cerr << "Failed to open file: " << filename << "\n";
        return "";
    }

    std::ostringstream str_stream{};
    file_stream >> str_stream.rdbuf();  // NOT str_stream << file_stream.rdbuf()

    if (file_stream.fail() && !file_stream.eof())
    {
        // Error reading file.
        std::cerr << "Failed to read file: " << filename << "\n";
        return "";
    }

    return str_stream.str();
}

void string_to_file(const std::string& filename, const std::string& str)
{
    std::ofstream myfile(filename);
    if (myfile.is_open())
    {
        myfile << str;
        myfile.close();
    }
}