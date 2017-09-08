#ifndef HTTP_PARSER_H_INCLUDED
#define HTTP_PARSER_H_INCLUDED

#include <cstdlib>
#include <memory>
#include "http/request.h"

namespace http {

class ParserImpl;

// STate machine for http parsing
class Parser {
public:

    enum Result {
        OK = 0,     // Chunk has been successfully consumed, wait for more
        DONE,   // Message parsing completed, may start form response
        ERROR   // Ups, I'm woman in love...
    };

    Parser();
    Result consume(const char*, const size_t length);
    inline Request& getRequest() {return _request;};

protected:
    Request _request;
    std::unique_ptr<ParserImpl> _impl;
};

// Interface for implementation class
class ParserImpl {
public:
    virtual Parser::Result consume(const char*, const size_t) = 0;
    virtual ~ParserImpl();
};

}

#endif // HTTP_PARSER_H_INCLUDED
