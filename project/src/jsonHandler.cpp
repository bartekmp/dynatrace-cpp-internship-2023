#include <iostream>

#include <boost/date_time/gregorian/gregorian.hpp>

#include "jsonHandler.h"

using namespace rapidjson;

namespace internship {
    // handling array beginning
    bool JsonHandler::StartArray() {
        // std::cout << "StartArray()" << std::endl;

        // ommitting first square bracket, not to make insideVerionsArray true
        if (jsonFileBeginning) {
            jsonFileBeginning = false;
        } else {

            // if object is OS, go through version array and find maxium period of time and it's coresponding cycle
            if (isOperatingSystem) {
                insideVerionsArray = true;
                maxDaysNumber = -1;
                maxCycle = std::string("", 0);
            }
        }

        return true;
    }

    // handling array end
    bool JsonHandler::EndArray(SizeType elementCount) {
        // std::cout << "EndArray(" << elementCount << ")" << std::endl;

        // one of two solutions:
        // 2) adding only the cycle with the longest support period
        if (insideVerionsArray) {
            if (maxDaysNumber != -1 && !maxCycle.empty()){
                data.emplace_back(name, maxCycle, maxDaysNumber);
            }
        }
        // (2

        // every array end (expect the last major one) comes out of the version array
        insideVerionsArray = false;

        // end of current system review
        isOperatingSystem = false;

        return true;
    }

    // handling object beginning
    bool JsonHandler::StartObject() {
        // std::cout << "StartObject()" << std::endl;

        // if new object detected and outside the versions array, seraching for name and os
        if (!insideVerionsArray) {
            nameKeyFound = false;
            osKeyFound = false;
        } 
        // else searching for next cycle, release date and end of life date
        else {
            cycleKeyFound = false;
            releaseDateKeyFound = false;
            eolKeyFound = false;
        }

        return true;
    }

    // handling object end
    bool JsonHandler::EndObject(SizeType memberCount) {
        // cout << "EndObject(" << memberCount << ")" << endl;
    
        if (insideVerionsArray) {
            if (!eol.empty() && !releaseDate.empty()) {
                int  daysNumber = days_between_dates(releaseDate, eol);

                
                // 1) adding all operating system version cycles
                // if (daysNumber > 0) {
                //     data.emplace_back(name, cycle, daysNumber);
                // }
                // (1

                // 2) adding only the longest operating system version cycle, adding in EndArray()
                if (daysNumber != -1) {
                    if (daysNumber > maxDaysNumber) { // or >= if want last occur
                        maxDaysNumber = daysNumber;
                        maxCycle = std::string(cycle);
                    }
                }
                // (2

            }
        }
        return true;
    }

    // handling keys
    bool JsonHandler::Key(const char* str, SizeType length, bool copy) {
        // std::cout << "Key(" << str << ", " << length << ", " << std::boolalpha << copy << ")" << std::endl;

        if (!insideVerionsArray) { 

            // if name key not found yet and key matches, name value is next
            if (!nameKeyFound && strcmp(str, "name") == 0) {
                nameKeyFound = true;
                nameValueNext = true;
            }

            // if name key has already been found (assuming that name comes before the os) and os key matches, os value is next
            if (nameKeyFound && !osKeyFound && strcmp(str, "os") == 0) {
                osKeyFound = true;
                osValueNext = true;
            }
        } else {

            // if cycle key not found yet and key matches, cycle value is next
            if (!cycleKeyFound && strcmp(str, "cycle") == 0) {
                cycleKeyFound = true;
                cycleValueNext = true;
            }

            // if cycle key has already been found (assuming that cycle comes before release date) and release date key matches, release date value is next
            if (cycleKeyFound && !releaseDateKeyFound && strcmp(str, "releaseDate") == 0) {
                releaseDateKeyFound = true;
                releaseDateValueNext = true;
            }

            // same as above, but found also "releasedDate" (not "releaseDate") strings in data2.json
            if (cycleKeyFound && !releaseDateKeyFound && strcmp(str, "releasedDate") == 0) {
                releaseDateKeyFound = true;
                releaseDateValueNext = true;
            }

            // if cycle key has already been found (assuming that cycle comes before end of life date) and end of life date key matches, end of life date value is next
            if (cycleKeyFound && !eolKeyFound && strcmp(str, "eol") == 0) {
                eolKeyFound = true;
                eolValueNext = true;
            }
        }

        return true;
    }

    //handling string
    bool JsonHandler::String(const char* str, SizeType length, bool copy) {
        // std::cout << "String(" << str << ", " << length << ", " << std::boolalpha << copy << ")" << std::endl;

        //getting key values when previously key handler setted it true
        if (!insideVerionsArray) {
            if (nameValueNext) {
                name = std::string(str, length);
                nameValueNext = false;
            }
        } else {

            if (cycleValueNext) {
                cycle = std::string(str, length);
                cycleValueNext = false;
            }

            if (releaseDateValueNext) {
                releaseDate = std::string(str, length);
                releaseDateValueNext = false;
            }

            if (eolValueNext) {
                eol = std::string(str, length);
                eolValueNext = false;
            }
        }

        return true;
    }

    //handling bool
    bool JsonHandler::Bool(bool b) {
        // std::cout << "Bool(" << std::boolalpha << b << ")" << std::endl;

        // if os key handler setted next value as true and it's value (b) is true it means that it is OS
        if (!insideVerionsArray) {
            if (osValueNext && b) {
                osValueNext = false;
                isOperatingSystem = true;
            }
        } else {

            // clearing eol values if it is boolean
            if (eolValueNext) {
                eol = std::string("", 0);
                eolValueNext = false;
            }

            // clearing relase date values if it is boolean
            if (releaseDateValueNext) {
                releaseDate = std::string("", 0);
                releaseDateValueNext = false;
            }
        }
        return true;
    }

    // handling null
    bool JsonHandler::Null() {
        // std::cout << "Null()" << std::endl;

        return true;
    }

    // handling int
    bool JsonHandler::Int(int i) {
        // std::cout << "Int(" << i << ")" << std::endl;

        return true;
    }

    // handling unsigned int
    bool JsonHandler::Uint(unsigned u) {
        // std::cout << "Uint(" << u << ")" << std::endl;

        return true;
    }

    // handling int64_t
    bool JsonHandler::Int64(int64_t i) {
        // std::cout << "Int64(" << i << ")" << std::endl;

        return true;
    }

    // handling uint64_t
    bool JsonHandler::Uint64(uint64_t u) {
        // std::cout << "Uint64(" << u << ")" << std::endl;

        return true;
    }

    // handling double
    bool JsonHandler::Double(double d) {
        // std::cout << "Double(" << d << ")" << std::endl;

        return true;
    }
    // sorting OS vector by support time descending-order
    void JsonHandler::sort_longest_support_os() {
        std::sort(data.begin(), data.end(), compare_support_period);
    }

    //displaying [elementsCount] vector's element
    void JsonHandler::display_longest_support_os(int elementsCount) {
        for (const auto& d: data) {
            std::cout << std::get<0>(d) << " " << std::get<1>(d) << " " << std::get<2>(d) << std::endl;
            if (elementsCount-- == 1) {
                break;
            }
        }
        // std::cout << "vec size: " << data.size() << std::endl;
    }
}