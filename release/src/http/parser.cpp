
#include "http/parser.h"
#include <http_parser.h>
#include <functional>
#include <utility>
#include <iostream>

namespace http {

class ParserImplementation: public ParserImpl {
public:
    ParserImplementation(Request& request): _request(request), _currentHeader(-1), _valueProcessed(false), _processingComplete(false) {

        http_parser_settings_init(&_http_parser_settings);

        _http_parser_settings.on_message_complete = [](http_parser* parser) -> int {
            return static_cast<ParserImplementation*>(parser->data)->onMessageComplete(parser);
        };

        _http_parser_settings.on_url = [](http_parser* parser, const char *p, size_t length) -> int {
            return static_cast<ParserImplementation*>(parser->data)->onUrl(parser, p, length);
        };

        _http_parser_settings.on_header_field = [](http_parser* parser, const char *p, size_t length) -> int {
            return static_cast<ParserImplementation*>(parser->data)->onHeaderField(parser, p, length);
        };

        _http_parser_settings.on_header_value = [](http_parser* parser, const char *p, size_t length) -> int {
            return static_cast<ParserImplementation*>(parser->data)->onHeaderValue(parser, p, length);
        };

        _http_parser_settings.on_body = [](http_parser* parser, const char *p, size_t length) -> int {
            return static_cast<ParserImplementation*>(parser->data)->onBody(parser, p, length);
        };

        http_parser_init(&_http_parser, HTTP_REQUEST);
        _http_parser.data = this;
    }

    int onMessageComplete(http_parser* parser) {
        _request.method = static_cast<Method>(parser->method);
        _request.version = parser->http_minor ? HttpVersion::V11 : HttpVersion::V10;
        _processingComplete = true;
        return 0;
    }

    int onUrl(http_parser* parser, const char *p, size_t length) {
        _request.uri += std::string(p, length);
        return 0;
    };

    int onHeaderField(http_parser* parser, const char *p, size_t length) {
        if (_valueProcessed || !_request.headers.size()) {
            // New header arrived
            ++_currentHeader;
            _request.headers.push_back(std::make_pair<std::string, std::string>(std::string(p, length), std::string()));
        } else {
            _request.headers[_currentHeader].first += std::string(p, length);
        }
        _valueProcessed = false;
        return 0;
    }

    int onHeaderValue(http_parser* parser, const char *p, size_t length) {
        _request.headers[_currentHeader].second += std::string(p, length);
        _valueProcessed = true;
        return 0;
    }

    int onBody(http_parser* parser, const char *p, size_t length) {
        _request.body += std::string(p, length);
        return 0;
    }

    Parser::Result consume(const char* p, const size_t length) {
        size_t consumed = http_parser_execute(
            &_http_parser,
            &_http_parser_settings,
            p,
            length
        );

        return _processingComplete
            ? Parser::DONE
            : consumed == length
                ? Parser::OK
                : Parser::ERROR;
    }

    Request& _request;
    http_parser_settings _http_parser_settings;
    http_parser _http_parser;
    int _currentHeader;
    bool _valueProcessed;
    bool _processingComplete;
};

Parser::Parser(): _request() {
    _impl = std::make_unique<ParserImplementation>(_request);
}

Parser::Result Parser::consume(const char* p, const size_t length) {
    return _impl->consume(p, length);
}

// To complete type
ParserImpl::~ParserImpl() {};

}
