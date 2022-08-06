#pragma once

#include <nlohmann/json.hpp>

// removes spaces at front and back of input string
std::string shrink_str(std::string& str) {
    int count = 0;
    auto it = str.begin();
    while (*it == ' ') {
        ++it;
        ++count;
    }

    if (count > 0) {
        str.erase(0, count);
        count = 0;
    }

    it = str.end();
    --it;
    while (*it == ' ') {
        --it;
        ++count;
    }
    if (count > 0) str.erase(str.length() - count - 1, count);
    return str;
}

nlohmann::json split_str(std::string& str, char divisor = ',') {
    auto result = nlohmann::json::array();
    int start = 0;
    std::string word;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == divisor) {
            word = str.substr(start, i - start);
            result.push_back(shrink_str(word));
            start = i + 1;
        }
    }
    word = str.substr(start, str.length() - start);
    result.push_back(shrink_str(word));
    return result;
}

nlohmann::json split_str(std::string str, char divisor = ',') {
    auto result = nlohmann::json::array();
    int start = 0;
    std::string word;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == divisor) {
            word = str.substr(start, i - start);
            result.push_back(shrink_str(word));
            start = i + 1;
        }
    }
    word = str.substr(start, str.length() - start);
    result.push_back(shrink_str(word));
    return result;
}
