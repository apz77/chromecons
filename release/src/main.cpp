#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <signal.h>

#include "config.h"
#include "sqlite3.h"
#include "http/server.h"
#include "router.h"

const std::string getPathToFile() {
#ifdef __linux__
    return (std::string(std::getenv("HOME")) + std::string("/.config/chromium/Default/Login Data"));
#else
    return "TODO: implement windows path";
#endif
}

int callback(void*, int argc, char** argv, char** azColName) {
    for(unsigned i = 0; i < argc; ++i) {
        std::cout<<argv[i];
        if (i < argc - 1) {
            std::cout<<" | ";
        }
    }
    std::cout<<std::endl;
    return 0;
}

int main() {
    std::cout<<"BastionPass Chrome passwords extractor "<<VERSION<<std::endl;
    sqlite3 *db;
    const std::string pathToFile = getPathToFile();
    int rc = sqlite3_open_v2(pathToFile.c_str(), &db, SQLITE_OPEN_READONLY, nullptr);
    if (rc != SQLITE_OK) {
        std::cout<<"Unable to open database at \""<<pathToFile<<"\", "<<sqlite3_errmsg(db)<<std::endl;
    } else {
        std::cout<<"Hurray!";
        const char* sql = "SELECT action_url, username_value, password_value FROM logins";
        char* errorMessage = nullptr;
        int result = sqlite3_exec(db, sql, callback, nullptr, &errorMessage);
        if (result != SQLITE_OK) {
            std::cout<<"Database retrieve error: "<<errorMessage<<std::endl;
        }
    }
    sqlite3_close(db);

    std::unique_ptr<Router> router(new Router());

    router->addSemanticRoute(http::Method::GET, {"terminate"}, [](const http::Request& request) -> http::Reply {
         http::Reply reply = http::Reply::getStandardReply(http::Reply::OK);
         reply.content = std::string("Thank you for using BastionPass.");
         reply.terminateServer = true;
         return reply;
    });

    http::Server server("127.0.0.1", "0", std::move(router));
    std::cout<<"Server started at "<<server.localEndpoint()<<std::endl;
    server.run();
    std::cout<<"Server terminated. Have a nice day."<<std::endl;

    getchar();
}
