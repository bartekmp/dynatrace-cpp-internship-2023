#include <string>

#include "internship.h"
#include "rapidjson/reader.h"

using namespace rapidjson;

namespace internship {
    class JsonHandler : public BaseReaderHandler<UTF8<>, JsonHandler> {
        private:

            // determines whether it's the beginning of a file (otherwise json object array)
            bool jsonFileBeginning = true;

            // determines whether we are in the verion (nested) array
            bool insideVerionsArray = false;

            // determines whether an object is a OS or not
            bool isOperatingSystem = false;

            // determine wheter a key loaded in a given step (key : value) is the key corresponding to the
            // one in a variable name. if changed to true, in next step will be properly used ([a-z]+ValueNext = true)
            // as it's value and remains true to the object end not to search for the same key again
            bool nameKeyFound = false;
            bool osKeyFound = false;
            bool cycleKeyFound = false;
            bool releaseDateKeyFound = false;
            bool eolKeyFound = false;

            // if changed true by finding a key, it will handle its value properly and then change back to false
            bool nameValueNext = false;
            bool osValueNext = false;
            bool cycleValueNext = false;
            bool releaseDateValueNext = false;
            bool eolValueNext = false;

            // specifies maximum number of days in the version array
            int maxDaysNumber;

            // specifies cycle name corresponding to maximum number of days
            std::string maxCycle;

            // values to store string values of their corresponding keys
            std::string name;
            std::string cycle;
            std::string releaseDate;
            std::string eol;

            // resposible for storaging the list of OS names, OS cycles and support periods in days
            std::vector<osCycleSupportItem> data;

        public:
            JsonHandler() {}

            // function called when array start detected
            //output:
            // [true]  - if has been successfully handled
            // [false] - else
            bool StartArray();

            //input : 
            // [SizeType], number of elements in array, if not needed may be ignored
            //output:
            // [true]  - if has been successfully handled
            // [false] - else
            bool EndArray(SizeType elementCount);

            // function called when object start detected
            //output:
            // [true]  - if has been successfully handled
            // [false] - else
            bool StartObject();

            // function called when object end detected
            //input: 
            // [SizeType], number of members in object, if not needed may be ignored
            //output:
            // [true]  - if has been successfully handled
            // [false] - else
            bool EndObject(SizeType memberCount);

            // function called when key detected
            //input:
            // str    : [char*], key string value
            // length : [SizeType], length of key string value
            // copy   : [bool], whether a key copy has been made: [true] - yes, [false] - no
            //output:
            // [true]  - if has been successfully handled
            // [false] - else
            bool Key(const char* str, SizeType length, bool copy);

            // function called when string detected
            //input:
            // str    : [char*], string value
            // length : [SizeType], length of string value
            // copy   : [bool], whether a key copy has been made: [true] - yes, [false] - no
            //output:
            // [true]  - if value has been successfully handled
            // [false] - else
            bool String(const char* str, SizeType length, bool copy);

            // function called when bool detected
            //input:
            // b : [bool], input boolean value
            //output:
            // [true]  - if value has been successfully handled
            // [false] - else
            bool Bool(bool b);

            // function called when null detected
            //output:
            // [true]  - if value has been successfully handled
            // [false] - else
            bool Null();

            // function called when int detected
            //input:
            // i : [int], input integer value
            //output:
            // [true]  - if value has been successfully handled
            // [false] - else
            bool Int(int i);

            // function called when unsigned detected
            //input:
            // u : [unsigned], input unsigned integer value
            //output:
            // [true]  - if value has been successfully handled
            // [false] - else
            bool Uint(unsigned u);

            // function called when int64_t detected
            //input:
            // i : [int64_t], input 64-bit integer value
            //output:
            // [true]  - if value has been successfully handled
            // [false] - else
            bool Int64(int64_t i);

            // function called when uint64_t detected
            //input:
            // u : [uint64_t], input unsigned 64-bit integer value
            //output:
            // [true]  - if value has been successfully handled
            // [false] - else
            bool Uint64(uint64_t u);

            // function called when double detected
            //input:
            // d : [double], input double value
            //output:
            // [true]  - if value has been successfully handled
            // [false] - else
            bool Double(double d);

            // function for sorting <tuple<string, string, int>> vector (that is (OS name, OS cycle, support period in days)) by int values
            void sort_longest_support_os();

            // function for displaying the first [elementsCount] <tuple<string, string, int>> vector's elements (that is (OS name, OS cycle, support period in days))
            //input:
            // elementsCount : [int], numbers of elements to be printed
            void display_longest_support_os(int elementsCount);
    };
}