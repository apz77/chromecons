#include "http/reply.h"

namespace http {

namespace constants {
    const std::string HTTP = "HTTP/";
    const std::string V10 = "1.0";
    const std::string V11 = "1.1";
    const std::string SPACE = " ";
    const std::string ENDL = "\r\n";

    const std::string OK = "OK";
    const std::string NO_CONTENT = "No Content";
    const std::string MOVED_PERMANENTLY = "Moved Permanently";
    const std::string MOVED_TEMPORARILY = "Moved Temporarily";
    const std::string NOT_MODIFIED = "Not Modified";
    const std::string BAD_REQUEST = "Bad Request";
    const std::string UNAUTHORIZED = "Unauthorized";
    const std::string FORBIDDEN = "Forbidden";
    const std::string NOT_FOUND = "Not Found";
    const std::string INTERNAL_SERVER_ERROR = "Internal Server Error";
    const std::string NOT_IMPLEMENTED = "Not Implemented";
    const std::string BAD_GATEWAY = "Bad Gateway";
}

std::string getDefaultMessage(const Reply::StatusCode code) {
    switch(code) {
        case Reply::StatusCode::OK: return constants::OK;
        case Reply::StatusCode::NO_CONTENT: return constants::NO_CONTENT;
        case Reply::StatusCode::MOVED_PERMANENTLY: return constants::MOVED_PERMANENTLY;
        case Reply::StatusCode::MOVED_TEMPORARILY: return constants::MOVED_TEMPORARILY;
        case Reply::StatusCode::NOT_MODIFIED: return constants::NOT_MODIFIED;
        case Reply::StatusCode::BAD_REQUEST: return constants::BAD_REQUEST;
        case Reply::StatusCode::UNAUTHORIZED: return constants::UNAUTHORIZED;
        case Reply::StatusCode::FORBIDDEN: return constants::FORBIDDEN;
        case Reply::StatusCode::NOT_FOUND: return constants::NOT_FOUND;
        case Reply::StatusCode::INTERNAL_SERVER_ERROR: return constants::INTERNAL_SERVER_ERROR;
        case Reply::StatusCode::NOT_IMPLEMENTED: return constants::NOT_IMPLEMENTED;
        case Reply::StatusCode::BAD_GATEWAY: return constants::BAD_GATEWAY;
        default: ;
    }
    return "";
}

Reply::Reply(): statusCode(Reply::StatusCode::INTERNAL_SERVER_ERROR), httpVersion(HttpVersion::V10), terminateServer(false) {}

Reply::Reply(Reply::StatusCode code, std::string cont): statusCode(code), content(cont), httpVersion(HttpVersion::V10), terminateServer(false) {}

std::vector<boost::asio::const_buffer> Reply::getBuffers() const {
    std::vector<boost::asio::const_buffer> buffers;

    buffers.push_back(boost::asio::buffer(constants::HTTP));
    buffers.push_back(boost::asio::buffer(httpVersion == HttpVersion::V10 ? constants::V10 : constants::V11));
    buffers.push_back(boost::asio::buffer(constants::SPACE));

    switch(statusCode) {
        case Reply::StatusCode::OK: buffers.push_back(boost::asio::buffer(constants::OK));
        case Reply::StatusCode::NO_CONTENT: buffers.push_back(boost::asio::buffer(constants::NO_CONTENT));
        case Reply::StatusCode::MOVED_PERMANENTLY: buffers.push_back(boost::asio::buffer(constants::MOVED_PERMANENTLY));
        case Reply::StatusCode::MOVED_TEMPORARILY: buffers.push_back(boost::asio::buffer(constants::MOVED_TEMPORARILY));
        case Reply::StatusCode::NOT_MODIFIED: buffers.push_back(boost::asio::buffer(constants::NOT_MODIFIED));
        case Reply::StatusCode::BAD_REQUEST: buffers.push_back(boost::asio::buffer(constants::BAD_REQUEST));
        case Reply::StatusCode::UNAUTHORIZED: buffers.push_back(boost::asio::buffer(constants::UNAUTHORIZED));
        case Reply::StatusCode::FORBIDDEN: buffers.push_back(boost::asio::buffer(constants::FORBIDDEN));
        case Reply::StatusCode::NOT_FOUND: buffers.push_back(boost::asio::buffer(constants::NOT_FOUND));
        case Reply::StatusCode::INTERNAL_SERVER_ERROR: buffers.push_back(boost::asio::buffer(constants::INTERNAL_SERVER_ERROR));
        case Reply::StatusCode::NOT_IMPLEMENTED: buffers.push_back(boost::asio::buffer(constants::NOT_IMPLEMENTED));
        case Reply::StatusCode::BAD_GATEWAY: buffers.push_back(boost::asio::buffer(constants::BAD_GATEWAY));
        default: buffers.push_back(boost::asio::buffer(constants::INTERNAL_SERVER_ERROR));
    }

    buffers.push_back(boost::asio::buffer(constants::ENDL));

    for(auto it = headers.begin(); it != headers.end(); ++it) {
        buffers.push_back(boost::asio::buffer(it->first));
        buffers.push_back(boost::asio::buffer(constants::SPACE));
        buffers.push_back(boost::asio::buffer(it->second));
        buffers.push_back(boost::asio::buffer(constants::ENDL));
    }

    buffers.push_back(boost::asio::buffer(constants::ENDL));

    buffers.push_back(boost::asio::buffer(content));

    return std::move(buffers);
}

Reply Reply::getStandardReply(Reply::StatusCode code) {
    return Reply(code, getDefaultMessage(code));
}

}
