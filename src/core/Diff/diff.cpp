#include <iostream>
#include "diff.h"
#include "diff_match_patch.h"
class Diff;

std::string diff_compare_strings(const std::string& s1, const std::string& s2)
{
	std::string result;
    diff_match_patch<std::string> dmp;
    auto diffs = dmp.diff_main(s1, s2);    
    dmp.diff_cleanupSemantic(diffs);

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

	return result;
}

std::string diff_compare_string_lines(const std::string& s1, const std::string& s2)  // Broken. FIXME!!
{
    std::string result;

    // Do the diff:
    diff_match_patch<std::string> dmp;
    auto diffs = dmp.diff_main(s1, s2);
    dmp.diff_cleanupSemantic(diffs);

    // Split the strings into lines:
    std::istringstream iss1(s1);
    std::istringstream iss2(s2);
    std::string line1, line2;
    std::vector<std::string> lines1, lines2;

    while (std::getline(iss1, line1)) {
        lines1.push_back(line1);
    }

    while (std::getline(iss2, line2)) {
        lines2.push_back(line2);
    }

    // line iterators:
    auto it1 = lines1.begin();
    auto it2 = lines2.begin();

    // Now iterate through the diffs:
    for (const auto& diff : diffs) {
        switch (diff.operation) {
        case dmp.INSERT:
            // std::cout << "\n + " << diff.text;
            result += "\n + " + *it2 + "\n";
            it2++;
            break;
        case dmp.DELETE:
            // std::cout << "\n - " << diff.text;
            result += "\n - " + *it1 + "\n";
            it1++;
            break;
        case dmp.EQUAL:
            // std::cout << "\n  " << diff.text;
            it1++;
            it2++;
            break;
        }
    }
    result += "\n";

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
    // return diff_compare_string_lines(text1, text2);  // Broken for now!
}