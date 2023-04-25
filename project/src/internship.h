#pragma once
#include <string>

namespace internship {
    // type for storing objects tuple<OS name, OS cycle, support period in days>
    typedef std::tuple<std::string, std::string, int> osCycleSupportItem;

    //input:
    // osElement1 : [tuple<string, string, int>], <OS name, OS cycle, support period in days>
    // osElement2 : [tuple<string, string, int>], <OS name, OS cycle, support period in days>
    //output:
    // [true]  - if osElement1.int > osElement2.int
    // [false] - else
    bool compare_support_period(const osCycleSupportItem& osElement1, const osCycleSupportItem& osElement2);

    //input:
    // releaseDate : [string], date of OS cycle release
    // eolDate     : [string], date of OS cycle life end
    //output:
    // [int] - number of days between eolDate and releaseDate, if date format = YYYY-MM-DD
    // [-1]  - else
    int days_between_dates(const std::string& releaseDate, const std::string& eolDate);

    //input:
    // jsonFileName  : [string], JSON filename
    // elementsCount : [int], number of elements with longest support to print
    void extract_os_longest_support(const std::string& jsonFileName, int elementsCount);

    //input:
    // jsonFileName  : [string], JSON filename
    // elementsCount : [int], number of elements with longest support to print
    void solution(const std::string& jsonFileName, int elementsCount);
}