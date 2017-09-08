#ifndef CHROME_RUNNER_H_INCLUDED
#define CHROME_RUNNER_H_INCLUDED

#include <string>

class ChromeRunner {
public:
    ChromeRunner(const std::string serverAddress);
    void openPage(const std::string page, bool pureAddress = false);
    std::string which() const {return _chromePath;};

    bool operator!() const {return _chromePath.empty();};

protected:
    std::string _serverAddress;
    std::string _chromePath;
};

#endif // CHROME_RUNNER_H_INCLUDED
