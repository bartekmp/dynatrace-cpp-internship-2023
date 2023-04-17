# Dynatrace Gdansk Summer Internship 2023 C++ Assignment
## The Theory
### EOL
EOL (short for end of life) is a date when the vendor's official support for a particular product ends and is provided no more.

### Used JSON structure
The JSON file used for this task is a list of objects, that follow this structure:
- `"name": <string value>` - a lower-case name of the product family, e.g. `debian`, `iphone` or `windows`
- `"os": <boolean value>` - a flag that tells whether this is an operating system or not, for example, `debian` has this set to `true`, while `iphone` to `false`
- `"versions": [<object>]` - a list of objects, each one of them describing a single version of the operating system, with the most notable:
    - `"cycle": <string value>` - the name of the particular version
    - `"releaseDate": <string value>` - the release date of this version
    - `"eol": <string value>` -  the end of life date of this version

There will be additional fields with all other kinds of information about the versions. 
An example of the JSON file may look like that:

```
[
    {
        "name": "debian",
        "os": true,
        "versions": [
        {
            "cycle": "11",
            "codename": "Bullseye",
            "releaseDate": "2021-08-14",
            "eol": "2024-07-01",
            "link": "https://www.debian.org/News/2022/20221217",
            "latest": "11.6",
            "lts": false
        },
        <...>
        ]
    },
    <...>
]
```
See the full example in `project/src/data/data.json`.

## The Task

Using C++17, write a command-line application that will extract a given number of operating systems with the longest support period from the provided JSON file.

**Clone this repository, write and call your solution in `project/src/internship.[h|cpp]`, and publish it on your profile. Send us back the link to the repository.**

You can put your own header and source files in the `project/src` directory.
Do not edit the `project/src/main.cpp` file.

You are allowed to use the libraries that are delivered within the project, see [Build environment](#build-environment) section for more info about building the application. We specifically require you to use our build project.

An operating system support period is defined as the number of days between the release date and the EOL date, including the end date day.

For instance, with the operating system release date 03.01.2023 and EOL date 04.08.2024 support length is 580 days.

Input format: `<JSON file name>` `<COUNT>`

Output format: descending-ordered (by the support period) `COUNT`-element long list of new-line separated rows, with elements split with spaces, in the format:
```
<OS name> <OS cycle> <support period in days>
```

For instance:
```
debian 11 1053
opensuse 15.4 541
ubuntu 22.10 274
```
**Note**: the JSON contains not only operating systems but also other different products. Values like dates in the JSON may be malformed or incorrectly formatted. Find other example JSON files in `project/data` folder.

## Assessment
Use this project skeleton to complete the task.

It is necessary to follow the exact output format, as all results will be validated, and an invalid output format will not be accepted. Besides correctness, also code quality and performance are important. We will run a set of tests to assess your code. Keeping the code clean, and avoiding certain code smells or antipatterns is a plus. See [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) to learn more.

Writing unit tests, to prove your solution is valid, is a plus and is going to be seen as an advantage. You can put them in `project/test` folder.

## Build environment
Use the environment placed in `project` directory. It is based on a Docker container with Ubuntu inside and leverages the GCC compiler with C++17 standard. You are free to write your code to finish the task. We also provide you with a set of libraries that may come in handy:
- to manipulate JSON files:
    - [`nlohmann/json`](https://github.com/nlohmann/json)
    - [`Tencent/rapidjson`](https://github.com/Tencent/rapidjson)
    - [`simdjson/simdjson`](https://github.com/simdjson/simdjson)
- to handle date time:
    - [`HowardHinnant/date`](https://github.com/HowardHinnant/date)
    - [`Boost.Date_Time`](https://www.boost.org/doc/libs/1_62_0/doc/html/date_time.html)
- to write unit tests:
    - [`Boost.Test`](https://www.boost.org/doc/libs/1_80_0/libs/test/doc/html/index.html)
    - [`Google Test`](https://google.github.io/googletest/)
- a subset of the general-purpose Boost libraries

See `project/Dockerfile` for more details.

To use it, install the latest Docker on your computer, ensure it is running, and use the following commands to build the application:
```
$ cd project
$ docker build -t internship_task .
$ docker run --rm -w /usr/src/internship_task -v "$(pwd):/usr/src/internship_task" -e DATA_JSON=src/data/data.json -e COUNT=5 internship_task:latest
```
- the second command will build a container image `internship_task` based on the latest Ubuntu with all appropriate components (compiler, libraries), 
- the third one will execute the `internship_task` image and:
    - will start the build of your sources with GCC compiler, producing the binary file `internship` in a new folder `project/build`,
    - will execute the program, providing `DATA_JSON` (path to JSON file, relative to `project` directory) and `COUNT` (number of elements to print) parameters via environment variables.

The first build run may take a while to complete. To rebuild your application, run the `internship_task` container again.

**Do not modify any of the build files/commands.**

The example code is placed in `project/src/internship.cpp` file is a simple showcase of how to access JSON programmatically using one of the libraries mentioned above. It reads the example JSON and prints all product names there.

## Notes
* Please be aware that the build will only work on machines that are X86-based. If you're working on ARM or other architectures, you might need to use a VM based on X86 architecture. The build was tested on Ubuntu 22.04 LTS x64.
* If running the `docker run` command fails with errors looking like `not found sh: 4`, etc., then please try to convert line endings of `project/entrypoint.sh` to LF, using `dos2unix` utility.