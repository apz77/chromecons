#ifndef ROUTER_H_INCLUDED
#define ROUTER_H_INCLUDED

#include <string>
#include <exception>
#include <map>
#include <initializer_list>
#include <string>

#include "http/server.h"

typedef std::map<std::string, std::string> ParameterBag;

/// Common interface for Route matching classes
class Route {
public:
    // Return true if method and uri matches this Route
    virtual std::pair<bool, ParameterBag> match(const http::Method, const std::string uri) const = 0;
};

/// Semantic URL part, between two slashes, may be just a string or parameter
class SemanticUrlPart {
public:
    SemanticUrlPart() = delete;

    /// If part starts with colon, then it's treated as parameter
    SemanticUrlPart(const std::string part);

    bool match(const std::string urlChunk) const;
    inline std::string name() const {return _name;};
    inline bool isParameter() const {return _isParameter;};

protected:
    std::string _name;
    bool _isParameter;
};

/// Semantic URL matcher, like /api/user/12345
class SemanticRoute: public Route {
public:
    SemanticRoute(http::Method, std::initializer_list<SemanticUrlPart>);
    SemanticRoute(http::Method, std::initializer_list<std::string>);

    // Returns pair of isMatch and parsed parameters map
    std::pair<bool, ParameterBag> match(const http::Method, const std::string uri) const;

protected:
    http::Method _method;
    std::vector<SemanticUrlPart> _parts;
};

typedef std::function<http::Reply(const http::Request&)> RequestFunc;

class Router: public http::RequestHandler {
public:
    Router();
    Router(RequestFunc defaultHandler);
    void addRoute(std::unique_ptr<Route>, RequestFunc);
    void addSemanticRoute(http::Method, std::initializer_list<std::string>, RequestFunc);
    void setDefaultHandler(RequestFunc h);

    http::Reply handleRequest(const http::Request&) const;

protected:
    std::vector<std::pair<std::unique_ptr<Route>, RequestFunc>> _routes;
    bool _hasDefaultHandler;
    RequestFunc _defaultHandler;
};

class RouterException: public std::exception {
public:
    RouterException(const std::string what): _what(what) {
    }
    const char* what() {return _what.c_str();}
protected:
    std::string _what;
};

class BadSemanticUrlPart: public RouterException {
public:
    BadSemanticUrlPart(const std::string what): RouterException(what) {};
};

#endif // ROUTER_H_INCLUDED
