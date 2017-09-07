#include "router.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>

namespace constants {
    const std::string slash = "/";
}

SemanticUrlPart::SemanticUrlPart(const std::string name) {
    if (!name.length()) {
        throw BadSemanticUrlPart(name);
    } else {
        if (name[0] == ':') {
            _name = boost::algorithm::to_lower_copy(name);
            _name.erase(_name.begin());
            _isParameter = true;
        } else {
            _name = boost::algorithm::to_lower_copy(name);
            _isParameter = false;
        }
    }
}

bool SemanticUrlPart::match(const std::string urlChunk) const {
    return _isParameter || _name == urlChunk;
}

SemanticRoute::SemanticRoute(http::Method method, std::initializer_list<SemanticUrlPart> parts): _parts(parts), _method(method) {
}

SemanticRoute::SemanticRoute(http::Method method, std::initializer_list<std::string> parts): _method(method) {
    for(auto it = parts.begin(); it != parts.end(); ++it) {
        _parts.emplace_back(SemanticUrlPart(*it));
    }
}

std::pair<bool, std::map<std::string, std::string>> SemanticRoute::match(const http::Method method, const std::string uri) const {
    if (method != _method) {
        return std::make_pair(false, std::map<std::string, std::string>());
    } else {
        std::map<std::string, std::string> parameters;
        std::vector<std::string> uriParts;

        std::string trimmedUri = boost::trim_left_copy_if(uri, boost::is_any_of(constants::slash));
        boost::algorithm::split(uriParts, trimmedUri, boost::is_any_of(constants::slash));

        auto uriIt = uriParts.begin();
        auto partIt = _parts.begin();
        for (; uriIt != uriParts.end() && partIt != _parts.end(); ++uriIt, ++partIt) {
            if (partIt->match(*uriIt)) {
                if (partIt->isParameter()) {
                    parameters.emplace(std::make_pair(partIt->name(), *uriIt));
                }
            } else {
                return std::make_pair(false, std::map<std::string, std::string>());
            }
        }
        // Exact match required
        if (uriIt == uriParts.end() && partIt == _parts.end()) {
            return std::make_pair(true, std::move(parameters));
        } else {
            return std::make_pair(false, std::map<std::string, std::string>());
        }
    }
}

Router::Router(): _hasDefaultHandler(false) {}

Router::Router(RequestFunc h): _hasDefaultHandler(true), _defaultHandler(h) {};

void Router::addRoute(std::unique_ptr<Route> route, RequestFunc requestFunc) {
    _routes.emplace_back(std::move(route), requestFunc);
}

void Router::addSemanticRoute(http::Method method, std::initializer_list<std::string> route, RequestFunc requestFunc) {
    _routes.emplace_back(std::make_unique<SemanticRoute>(method, route), requestFunc);
}

http::Reply Router::handleRequest(const http::Request& request) const {
    for(auto it = _routes.begin(); it != _routes.end(); ++it) {
        bool result;
        ParameterBag parameters;
        std::tie(result, parameters) = it->first->match(request.method, request.uri);
        if (result) {
            return it->second(request);
        }
    }

    if (_hasDefaultHandler) {
        return _defaultHandler(request);
    } else {
        return http::Reply::getStandardReply(http::Reply::NOT_IMPLEMENTED);
    }
}
