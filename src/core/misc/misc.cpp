#include "misc.h"
#include <cmath>


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

std::string pmp_str(std::vector<std::string>& tokens, const std::string& pre, const std::string& mid, const std::string& post)
{
    std::string s(pre);
    bool first_pass = true;
    for (const auto& token : tokens)
    {
        if (!first_pass)
        {
            s.append(mid);
        }
        first_pass = false;
        s.append(token);
    }
    s.append(post);
    return s;
}

std::string pmp_str(std::set<std::string>& tokens, const std::string& pre, const std::string& mid, const std::string& post)
{
    std::string s(pre);
    bool first_pass = true;
    for (const auto& token : tokens)
    {
        if (!first_pass)
        {
            s.append(mid);
        }
        first_pass = false;
        s.append(token);
    }
    s.append(post);
    return s;
}

// from here:
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split_str(const std::string& s1, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;

    while ((pos_end = s1.find(delimiter, pos_start)) != std::string::npos) {
        token = s1.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }
    result.push_back(s1.substr(pos_start));
    return result;
}

/*
std::string float_to_str(double f, int digits)  // Not super happy with this implementation! What if the decimal points are all 0's?
{
    std::string s = std::to_string(f);
    size_t dot_pos = s.find_first_of(".");
    if (dot_pos == std::string::npos)  // Found an integer
    {
        return s;
    }
    std::string head = s.substr(0, dot_pos);
    std::string tail = s.substr(dot_pos, digits + 1);
    return head + tail;
}
*/

bool double_eq(double F1, double F2) {
    if (std::abs(F1 - F2) < EPSILON) {
        return true;
    }
    return false;
}

int ipower(int a, int n)  // From here: https://stackoverflow.com/questions/1505675/power-of-an-integer-in-c
{
    int res = 1;  // Please test it is correct!
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

std::string float_to_str(double F1, unsigned int places) {
    if (double_eq(F1, std::round(F1))) {
        return std::to_string(static_cast<long long int>(std::round(F1)));
    }
    std::ostringstream buffer;
    int tens = ipower(10, places);           // Need to test it works, but it should be correct.
    buffer << std::round(F1 * tens) / tens;
    return buffer.str();
}

std::string bool_to_str(bool B1)
{
    if (B1)
    {
        return "yes";
    }
    return "no";
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
