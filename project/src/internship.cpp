#include <iostream>

#include "rapidjson/reader.h"
#include "rapidjson/filereadstream.h"

#include <boost/date_time/gregorian/gregorian.hpp>

#include "internship.h"
#include "jsonHandler.h"

using namespace rapidjson;

namespace internship {
    bool compare_support_period(const osCycleSupportItem& osElement1, const osCycleSupportItem& osElement2) {
        return std::get<2>(osElement1) > std::get<2>(osElement2);
    }

    int days_between_dates(const std::string& releaseDate, const std::string& eolDate) {
        try {
            // creating dates from string
            auto dateStart = boost::gregorian::from_string(releaseDate);
            auto dateEnd = boost::gregorian::from_string(eolDate);

            // calculating the dates difference
            auto dateDiff = dateEnd - dateStart;

            return dateDiff.days() + 1;
        } catch (const std::exception& e) {
            // std::cerr << "Failed to calculate: releaseDate="  << releaseDate << ", eolDate=" << eolDate << std::endl;
            return -1;
        }
    }

    void extract_os_longest_support(const std::string& jsonFileName, int elementsCount) {
        if (elementsCount < 1) {
            return;
        }

        FILE* file = fopen(jsonFileName.c_str(), "r");
        if  (!file) {
            std::cerr << "Failed to open file: " << jsonFileName << std::endl;
            exit(1);
        }

        // setting buffer to 64KB, by default rapidJSON's buffor is 4KB
        char buffer[65536];

        // reading from the input file
        FileReadStream is(file, buffer, sizeof(buffer));

        // parsing the JSON data from the stream
        JsonHandler jsonHandler;
        Reader reader;
        reader.Parse(is, jsonHandler);

        // sorting and displaying the first [elementsCount] operating systems
        jsonHandler.sort_longest_support_os();
        jsonHandler.display_longest_support_os(elementsCount);
    }

    void solution(const std::string& jsonFileName, int elementsCount) {
        extract_os_longest_support(jsonFileName, elementsCount);
    }
}