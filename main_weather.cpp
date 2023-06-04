#include <iostream>
#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        return 1;
    }

    if (atoi(argv[1]) < 0 || atoi(argv[1]) > 24) {
        return 2;
    }

    // IP

    httplib::Client cli1("https://whatsmyip.dev");
    auto result = cli1.Get("/api/ip");

    json data = json::parse(result->body);

    std::string ip = data["addr"];

    // Coordinates

    std::string request = "/json/" + ip;

    httplib::Client cli2("http://ip-api.com");
    result = cli2.Get(request);

    data = json::parse(result->body);

    auto latitude = to_string(data["lat"]);
    auto longtitude = to_string(data["lon"]);

    // Weather information

    request = "/v1/forecast?latitude=" + latitude + "&longitude=" + longtitude + "&hourly=temperature_2m&forecast_days=2";

    httplib::Client cli3("https://api.open-meteo.com");
    result = cli3.Get(request);

    data = json::parse(result->body);

    int neccessery_temperature_index = atoi(argv[1]) + 24;

    std::cout << "Температура завтра в " << argv[1] << " часов : " << data["hourly"]["temperature_2m"][neccessery_temperature_index] << '\n';

    return 0;
}