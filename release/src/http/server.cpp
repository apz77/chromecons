// inplementation of http server

#include "http/server.h"
#include <signal.h>
#include <iostream>

namespace http {

Server::Server(const std::string& address, const std::string& port, std::unique_ptr<RequestHandler> handler):
    _requestHandler(std::move(handler)),
    _io_service(),
    _signals(_io_service),
    _acceptor(_io_service),
    _socket(_io_service) {

    // Register system signals to terminate server correctly
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
#if defined(SIGQUIT)
    _signals.add(SIGQUIT);
#endif // defined

    _start_wait_for_signals();

    boost::asio::ip::tcp::resolver resolver(_io_service);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port}); //Initializer list
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();
    _start_accepting();
}

boost::asio::ip::tcp::endpoint Server::localEndpoint() {return _acceptor.local_endpoint();}

void Server::_start_accepting() {
    _acceptor.async_accept(_socket,
       [this](boost::system::error_code ec) {
            if (_acceptor.is_open() && !ec) {
                auto newConnection = std::make_shared<Connection>(
                    std::move(_socket),
                    *this
                );
                _connections.insert(newConnection);
                newConnection->start();
            }

            if (_acceptor.is_open()) {
                _start_accepting();
            }
       }
    );
}

void Server::_start_wait_for_signals() {
    _signals.async_wait(
        [this](boost::system::error_code, int) {
            _acceptor.close();
        }
    );
}

void Server::stopConnection(std::shared_ptr<Connection> connection) {
    _connections.erase(connection);
    connection->stop();
}

void Server::run() {
    _io_service.run();
}

void Server::stop() {
    _io_service.stop();
}

Reply Server::handleRequest(Request& request) {
    return _requestHandler->handleRequest(request);
}
}
