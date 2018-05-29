#ifndef HTTP_REQUEST_H_INCLUDED
#define HTTP_REQUEST_H_INCLUDED

#include <utility>
#include <string>
#include <vector>

namespace http {

enum Method {
    DELETE_METHOD = 0,
    GET_METHOD,
    HEAD_METHOD,
    POST_METHOD,
    PUT_METHOD,
    CONNECT_METHOD,
    OPTIONS_METHOD,
};

enum HttpVersion {
    V10,
    V11
};

typedef std::pair<std::string, std::string> Header;

class Request {
public:
    Method method;
    std::string uri;
    HttpVersion version;
    std::vector<Header> headers;
    std::string body;
};

}

#endif // HTTP_REQUEST_H_INCLUDED
