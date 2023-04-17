#include <chrono>
#include <fstream>
#include <iostream>

#include <date/date.h>
#include <nlohmann/json.hpp>

#include "internship.h"

using json = nlohmann::json;
using namespace date;

namespace internship {
    // remove this function before submitting your solution
    void example(const std::string& jsonFileName) {
        std::ifstream f(jsonFileName);
        json data = json::parse(f);

        std::cout << "Dynatrace Gdansk Summer Internship 2023\n"
                    << "UTC time now: " << std::chrono::system_clock::now() << "\n\n";

        for(const auto& [id, product] : data.items()) {
            std::cout << "Product name: " << product["name"] << "\n";
        }
    }

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount) {
        example(jsonFileName); // remove this call before submitting your solution

        // put the call to your solution here
    }
}