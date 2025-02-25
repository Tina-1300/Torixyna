#pragma once
#include <iostream>
#include <sstream>

template <typename T>
void print(const T& value){
    std::cout << value << "\n";
};

template <typename First, typename... Rest>
void print(const First& first, const Rest&... rest){
    std::cout << first << "";
    print(rest...);
};

template <typename T>
T input(const std::string& prompt = ""){
    if (!prompt.empty()){
        std::cout << prompt;
    }
    std::string line;
    std::getline(std::cin, line);
    std::istringstream stream(line);
    T value;
    stream >> value;
    return value;
};

template <>
std::string input<std::string>(const std::string& prompt){
    if (!prompt.empty()){
        std::cout << prompt;
    }
    std::string line;
    std::getline(std::cin, line);
    return line;
};
