#include "misc.h"

std::string file_to_string(const std::string& filename, bool verbose)
{
    std::ifstream file_stream{filename};

    if (file_stream.fail())
    {
        // Error opening file.
        if (verbose)
        {
            std::cerr << "Failed to open file: " << filename << "\n";
        }
        return "";
    }

    std::ostringstream str_stream{};
    file_stream >> str_stream.rdbuf();  // NOT str_stream << file_stream.rdbuf()

    if (file_stream.fail() && !file_stream.eof())
    {
        // Error reading file.
        if (verbose)
        {
            std::cerr << "Failed to read file: " << filename << "\n";
        }
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

bool test_files_equal(const std::string& filename1, const std::string& filename2)
{
    std::string s1 = file_to_string(filename1);
    std::string s2 = file_to_string(filename2);
    return s1 == s2;
}

bool create_directory(const std::string& path)
{
    if (!std::filesystem::exists(path)) {
        if (std::filesystem::create_directory(path)) {
            std::cout << "Directory created: " << path << std::endl;
            return true;
        }
        else {
            std::cerr << "Failed to create directory: " << path << std::endl;
            return false;
        }
    }
    else {
        // std::cout << "Directory already exists: " << directoryPath << std::endl;
        return true;
    }
}

bool delete_file(const std::string& filename, bool verbose)
{
    if (std::filesystem::exists(filename)) {
        if (std::filesystem::remove(filename)) {
            if (verbose)
            {
                std::cout << "File deleted: " << filename << std::endl;
            }
            return true;
        }
        else {
            if (verbose)
            {
                std::cerr << "Failed to delete file: " << filename << std::endl;
            }
            return false;
        }
    }
    else {
        if (verbose)
        {
            std::cout << "File does not exist: " << filename << std::endl;
        }
        return false;
    }
}

std::string remove_extension(const std::string& filename, const std::string& ext)
{
    size_t ext_pos = filename.rfind(ext);
    if (ext_pos == std::string::npos) { return filename; }
    return filename.substr(0, ext_pos);
}

bool has_extension(const std::string& filename)
{
    if (filename.find(".") != std::string::npos)
    {
        return true;
    }
    return false;
}

std::string getCurrentDateTimeString(const std::string& date_sep, const std::string& date_time_sep, const std::string& time_sep) {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    // ss << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S");
    std::string format_str = "%Y" + date_sep + "%m" + date_sep + "%d";
    format_str += date_time_sep;
    format_str += "%H" + time_sep + "%M" + time_sep + "%S";
    ss << std::put_time(std::localtime(&currentTime), format_str.c_str());

    return ss.str();
}

std::string indent(int width)
{
    std::string s;
    for (int i = 0; i < width; i++)
    {
        s.append(" ");
    }
    return s;
}

std::string pad_digits(int number, int width)
{
    std::string str_number = std::to_string(number);
    int number_width = static_cast<int>(str_number.size());
    if (number_width >= width)
    {
        return str_number;
    }
    int delta_width = width - number_width;
    std::string padding;
    for (int i = 0; i < delta_width; i++)
    {
        padding.append("0");
    }
    return padding + str_number;
}

std::string pad_str_right(std::string s, int width)
{
    int s_width = static_cast<int>(s.size());
    if (s_width >= width)
    {
        return s;
    }
    int delta_width = width - s_width;
    std::string padding;
    for (int i = 0; i < delta_width; i++)
    {
        padding.append(" ");
    }
    return s + padding;
}

std::string pad_str(std::string s, std::string delim, int width, bool left)
{
    int s_width = static_cast<int>(s.size());
    if (s_width >= width)
    {
        return s;
    }
    int delta_width = width - s_width;
    std::string padding;
    for (int i = 0; i < delta_width; i++)
    {
        padding.append(delim);
    }
    if (left)
    {
        return padding + s;
    }
    return s + padding;
}

std::string format_string(std::string s, std::vector<std::string>& params)
{
    if (params.size() == 0)
    {
        return s;
    }
    size_t param_loc = s.find_first_of("{}");
    if (param_loc == std::string::npos)
    {
        return s;
    }
    std::string result = s.substr(0, param_loc);
    result.append(params[0]);
    s = s.substr(param_loc + 2);
    for (size_t i = 1; i < params.size(); i++)
    {
        param_loc = s.find_first_of("{}");
        if (param_loc == std::string::npos)
        {
            return result + s;
        }
        std::string head = s.substr(0, param_loc);
        result.append(head);
        result.append(params[i]);
        s = s.substr(param_loc + 2);
    }
    return result + s;
}

std::string format_string(std::string s, std::string p1)
{
    std::vector<std::string> params;
    params.push_back(p1);
    return format_string(s, params);
}

std::string format_string(std::string s, std::string p1, std::string p2)
{
    std::vector<std::string> params;
    params.push_back(p1);
    params.push_back(p2);
    return format_string(s, params);
}

std::string format_string(std::string s, std::string p1, std::string p2, std::string p3)
{
    std::vector<std::string> params;
    params.push_back(p1);
    params.push_back(p2);
    params.push_back(p3);
    return format_string(s, params);
}

std::string format_string(std::string s, std::string p1, std::string p2, std::string p3, std::string p4)
{
    std::vector<std::string> params;
    params.push_back(p1);
    params.push_back(p2);
    params.push_back(p3);
    params.push_back(p4);
    return format_string(s, params);
}

std::string format_string(std::string s, std::string p1, std::string p2, std::string p3, std::string p4, std::string p5)
{
    std::vector<std::string> params;
    params.push_back(p1);
    params.push_back(p2);
    params.push_back(p3);
    params.push_back(p4);
    params.push_back(p5);
    return format_string(s, params);
}
