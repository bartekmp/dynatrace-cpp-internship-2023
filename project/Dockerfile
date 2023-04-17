# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest
LABEL description="Dynatrace Gdansk Summer Internship 2023"

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

#############
# Install the dependencies
RUN apt-get -y install build-essential pkg-config git curl unzip zip tar
RUN cd /opt && git clone https://github.com/microsoft/vcpkg && ./vcpkg/bootstrap-vcpkg.sh
ENV PATH="${PATH}:/opt/vcpkg"

# Install JSON libraries
## nlohmann/json, Tencent/rapidjson, simdjson/simdjson
RUN vcpkg install nlohmann-json rapidjson simdjson

# Install date-handling library
## HowardHinnant/date
RUN vcpkg install date

# Install unit test libraries
## gtest, boost-test
RUN vcpkg install gtest boost-test

# Install BOOST libraries
RUN vcpkg install boost-accumulators boost-algorithm boost-any boost-array \
boost-assert boost-bimap boost-chrono boost-container boost-convert boost-core boost-date-time \
boost-format boost-json boost-lexical-cast boost-range boost-sort boost-tokenizer

# Specify the working directory
WORKDIR /usr/src/internship_task

#############
# Run the program
CMD ["sh", "entrypoint.sh"]