#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "config.h"
#include "http/server.h"
#include "router.h"
#include "password_retriever.h"
#include "chrome_runner.h"
#include "stock_content.h"
#include "utils.h"

int main(int argc, char** argv) {
    std::cout<<"BastionPass Chrome passwords extractor "<<VERSION<<std::endl;
    PasswordRetriever passwordRetriever(getPathToFile());

    std::unique_ptr<Router> router(new Router());

    router->addSemanticRoute(http::Method::GET_METHOD, {"terminate"}, [](const http::Request& request) -> http::Reply {
         http::Reply reply = http::Reply::getStandardReply(http::Reply::OK);
         reply.content = std::string("Thank you for using BastionPass.");
         reply.terminateServer = true;
         return reply;
    });

    router->addSemanticRoute(http::Method::GET_METHOD, {"blocked"}, [](const http::Request& request) -> http::Reply {
         http::Reply reply = http::Reply::getStandardReply(http::Reply::OK);
         reply.content = generateStockContent("No passwords found", "Please, close Chrome or Chromium", "We cannot retrieve Chrome or Chromuim passwords while it's running. Please, close it and rerun the utility.");
         reply.terminateServer = true;
         return reply;
    });

    router->addSemanticRoute(http::Method::GET_METHOD, {"nopasswords"}, [](const http::Request& request) -> http::Reply {
         http::Reply reply = http::Reply::getStandardReply(http::Reply::OK);
         reply.content = generateStockContent(
              "No password found",
              "No passwords found stored locally.",
              "Sorry, but we could not find any Chrome or Chromuim passwords stored on your PC :("
              "<br/><a href=\"/removeyourself\">Click here to remove this utility from your PC.</a>"
              "<br/><a href=\"https://app.bastionpass.com/\">Proceed to your BastionPass</a>"
          );
         return reply;
    });

    router->addSemanticRoute(http::Method::GET_METHOD, {"removeyourself"}, [argc, argv](const http::Request& request) -> http::Reply {
         http::Reply reply = http::Reply::getStandardReply(http::Reply::OK);
         reply.content = generateStockContent(
              "Utility removed", "The utility has been removed from your PC.",
              "Thank you for using BastionPass!"
              "<br/><a href=\"https://app.bastionpass.com/\">Proceed to your BastionPass</a>");
         reply.terminateServer = true;
         selfDesctruct(argc, argv);
         return reply;
    });

    router->addSemanticRoute(http::Method::OPTIONS_METHOD, {"passwords"}, [&passwordRetriever](const http::Request& request) -> http::Reply {
         http::Reply reply = http::Reply::getStandardReply(http::Reply::OK);
         reply.headers.emplace_back("Access-Control-Allow-Origin", "*");
         return reply;
    });

    router->addSemanticRoute(http::Method::GET_METHOD, {"passwords"}, [&passwordRetriever](const http::Request& request) -> http::Reply {
         http::Reply reply = http::Reply::getStandardReply(http::Reply::OK, request.version);
         reply.headers.emplace_back("Access-Control-Allow-Origin", "*");
         reply.headers.emplace_back("Content-Type", "application/json");
         reply.content = toJson(passwordRetriever.begin(), passwordRetriever.end());
         return reply;
    });

    http::Server server("127.0.0.1", "0", std::move(router));
    std::cout<<"Server started at "<<server.localEndpoint()<<std::endl;
    std::cout<<"Press Ctrl-C to terminate"<<std::endl;

    std::stringstream address;
    address<<server.localEndpoint();

    ChromeRunner chromeRunner(address.str());

    if (!chromeRunner) {
        std::cerr<<"No chrome or chromium found on your system :("<<std::endl;
        exit(1);
    } else {
        std::cout<<"Chrome detected: "<<chromeRunner.which()<<std::endl;
    }

    if (!passwordRetriever) {
        if (passwordRetriever.isDBLocked()) {
            chromeRunner.openPage("/blocked");
            std::cerr<<"Chrome password database is not available while chrome or chromium is running. Please close them and rerun this utility"<<std::endl;
        } else {
            chromeRunner.openPage("/nopasswords");
            std::cerr<<"We were unable to grab your chrome passwords. Probably they are not stored locally."<<std::endl;
            std::cerr<<"Some techincal staff: "<<passwordRetriever.errorCode()<<" " <<passwordRetriever.getSqliteErrorMessage()<<std::endl;
        }
    } else {
        // Everything is OK, proceed import
        chromeRunner.openPage("https://app.bastionpass.com/chromeimport?server=" + address.str(), true);
    }

    // Automatically shutdown the server in 10 minutes
    boost::asio::deadline_timer timer(server.getIOService(), boost::posix_time::seconds(10 * 60));
    timer.async_wait([&server](const boost::system::error_code&) {
        std::cout<<"Server shutdowns due to runtime is out."<<std::endl;
        server.stop();
    });

    server.run();
    std::cout<<"Server terminated. Have a nice day."<<std::endl;
}
