#include <iostream>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace nlohmann::literals;

json finder(std::string key, json object);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        return 1;
    }

    std::ifstream f(argv[1]);
    json data = json::parse(f);
    json answer = data;
    std::string path_str = argv[2];

    std:: cout << finder(path_str, data) << '\n';

    return 0;
}

json finder(std::string path, json object) {  //алгоритм рекурсивного спуска
    std::string buffer;
    std::string next_path;
    json answer;
    int i = 0;

    for (auto it = path.begin(); it <= path.end(); it++) {
        if (*it == '.') {
            next_path = path.substr(i+1);
            if (buffer != "*") {
                return finder(next_path, object[buffer]);
            } else {
                for (auto iter = object.begin(); iter != object.end(); iter++) {
                    answer += finder(next_path, *iter);
                }
                return answer;
            }
        }

        if (it == path.end()) {
            return object[buffer];
        }

        i++;
        buffer = buffer + *it;
    }

    throw "Exeption 1!";
}