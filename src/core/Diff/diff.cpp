#include <iostream>
#include "diff.h"
#include "diff_match_patch.h"
class Diff;

std::string diff_compare_strings(const std::string& s1, const std::string& s2)
{
	std::string result;
    diff_match_patch<std::string> dmp;

    // std::list<Diff> diffs = dmp.diff_main(s1, s2);
    auto diffs = dmp.diff_main(s1, s2);
    
    dmp.diff_cleanupSemantic(diffs);

    // std::cout << "String 1: " << s1 << std::endl;
    // std::cout << "String 2: " << s2 << std::endl;
    // std::cout << "Diff: ";

    for (const auto& diff : diffs) {
        switch (diff.operation) {
        case dmp.INSERT:
            // std::cout << "\n + " << diff.text;
            result += "\n + " + diff.text;
            break;
        case dmp.DELETE:
            // std::cout << "\n - " << diff.text;
            result += "\n - " + diff.text;
            break;
        case dmp.EQUAL:
            // std::cout << "\n  " << diff.text;
            break;
        }
    }
    result += "\n";

    // std::cout << std::endl;
	return result;
}

std::string diff_compare_files(const std::string& file1, const std::string& file2)
{
    std::string text1 = file_to_string(file1);
    std::string text2 = file_to_string(file2);

    if (text1 == text2)
    {
        return "";
    }
    return diff_compare_strings(text1, text2);
}