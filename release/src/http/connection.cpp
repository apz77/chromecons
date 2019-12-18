// Implementation of connection.h

#include "http/connection.h"
#include "http/server.h"
#include <iostream>
#include <vector>

namespace http {

Connection::Connection(boost::asio::ip::tcp::socket socket, Server& server): _socket(std::move(socket)), _server(server), _parser() {
}

void Connection::start() {
    _socket.async_read_some(
        boost::asio::buffer(_buffer),
        [this](boost::system::error_code ec, std::size_t bytesReceived) {
            Parser::Result result;
            if (!ec && (result = _parser.consume(_buffer.data(), bytesReceived)) != Parser::ERROR_RESULT) {
                if (result == Parser::OK_RESULT) {
                    start();
                } else {
                    Reply reply = std::move(_server.handleRequest(_parser.getRequest()));
                    auto b = reply.getBuffers();
                    std::vector<char> data(boost::asio::buffer_size(b));
                    boost::asio::buffer_copy(boost::asio::buffer(data), b);
                    writeReply(reply);
                }
            } else {
                _server.stopConnection(shared_from_this());
            }
        }
    );
}

void Connection::writeReply(Reply reply) {
    _socket.async_write_some(
        reply.getBuffers(),
        [this, reply](boost::system::error_code ec, size_t) {
            if (!ec) {
                boost::system::error_code no_error;
                _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, no_error);
            } else if (ec != boost::asio::error::operation_aborted) {
                _server.stopConnection(shared_from_this());
            }
            if (reply.terminateServer) {
                _server.stop();
            }
    });
}

void Connection::stop() {
    _socket.close();
}

}
