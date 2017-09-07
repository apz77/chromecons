#ifndef REPLY_H_INCLUDED
#define REPLY_H_INCLUDED

#include "http/request.h"
#include <memory>
#include <boost/asio.hpp>

namespace http {

class Reply {
public:
    enum StatusCode {
        OK = 200,
        NO_CONTENT = 204,
        MOVED_PERMANENTLY = 301,
        MOVED_TEMPORARILY = 302,
        NOT_MODIFIED = 304,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        INTERNAL_SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
        BAD_GATEWAY = 502
    };

    Reply();
    Reply(StatusCode, std::string);

    std::vector<boost::asio::const_buffer> getBuffers() const;

    HttpVersion httpVersion;
    StatusCode statusCode;
    std::vector<Header> headers;
    std::string content;

    bool terminateServer;

    static Reply getStandardReply(const StatusCode);
};

}

#endif // REPLY_H_INCLUDED
