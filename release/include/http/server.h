// Simple http server

#ifndef HTTP_SERVER_H_INCLUDED
#define HTTP_SERVER_H_INCLUDED

#include <boost/asio.hpp>
#include <set>
#include <memory>
#include "http/connection.h"

namespace http {

class RequestHandler;

class Server {
public:
    Server() = delete;
    Server& operator=(const Server&) = delete;

    // Creates an Http server, and bind it to address and port
    explicit Server(const std::string& address, const std::string& port, const std::unique_ptr<RequestHandler>);

    boost::asio::ip::tcp::endpoint localEndpoint();
    boost::asio::io_service& getIOService() {return _io_service;};

    void run();
    void stop();

protected:
    boost::asio::io_service _io_service;
    boost::asio::signal_set _signals;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ip::tcp::socket _socket;

    void _start_wait_for_signals();
    void _start_accepting();

    Reply handleRequest(Request&);

    void stopConnection(std::shared_ptr<Connection>);

    std::set<std::shared_ptr<Connection>> _connections;

    std::unique_ptr<RequestHandler> _requestHandler;



friend class Connection;
};

// Implement your own RequestHandler
class RequestHandler {
public:
    // Might be called async, don't use global mutable variables
    virtual Reply handleRequest(const Request&) const = 0;
};

}


#endif // HTTP_SERVER_H_INCLUDED
