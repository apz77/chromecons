#include "chrome_runner.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/algorithm/string.hpp>

#ifdef __linux__
#include <linux/limits.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#endif // __linux__

#ifdef __linux__
bool checkLinuxCommandExists(const std::string name) {
    std::string command = "which " + name + " 2>/dev/null";
    char buffer[PATH_MAX];
    FILE* f = popen(command.c_str(), "r");

    if (!f || !fgets(buffer, PATH_MAX, f)) {
        return false;
    }
    pclose(f);

    std::string path = boost::trim_copy_if(std::string(buffer), boost::is_any_of(" \t\r\n\b"));
    auto result = access(path.c_str(), F_OK);
    return result != -1;
}
#endif // __linux__

ChromeRunner::ChromeRunner(const std::string serverAddress): _serverAddress(serverAddress) {
    _chromePath = "";
#ifdef __linux__
    // Linux distributions chrome commiters are just crazy.
    std::vector<std::string> possibleChromes({"google-chrome", "google-chrome-stable", "chrome", "chromium", "chromium-browser"});
    auto result = std::find_if(possibleChromes.begin(), possibleChromes.end(), [](const std::string& chrome) -> bool {return checkLinuxCommandExists(chrome);});
    if (result != possibleChromes.end()) {
        _chromePath = *result;
    }
#else
    // Todo: implement windows lookup here
#endif
}

void ChromeRunner::openPage(const std::string page, bool pureAddress) {
    std::string path = _chromePath + " " + (pureAddress ? page : (_serverAddress + page));
    std::cout<<"Launching "<<path<<std::endl;
    std::system(path.c_str());
}
