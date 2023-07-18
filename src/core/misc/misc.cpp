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
