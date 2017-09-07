#ifndef HTTP_CONNECTION_H_INCLUDED
#define HTTP_CONNECTION_H_INCLUDED

#include <memory>
#include <array>
#include <boost/asio.hpp>
#include "http/parser.h"
#include "http/reply.h"

namespace http {

class Server;

class Connection: public std::enable_shared_from_this<Connection> {
public:
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    explicit Connection(
        boost::asio::ip::tcp::socket,
        Server&
    );

    void start();
    void stop();

protected:
    boost::asio::ip::tcp::socket _socket;
    Server& _server;
    std::array<char, 65536> _buffer;
    Parser _parser;

    void writeReply(Reply);
};

}

#endif // HTTP_CONNECTION_H_INCLUDED
