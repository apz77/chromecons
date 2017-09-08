#ifndef PASSWORD_RETRIEVER_H_INCLUDED
#define PASSWORD_RETRIEVER_H_INCLUDED

#include <string>
#include <vector>

class PasswordRecord {
public:
    PasswordRecord(std::string u, std::string l, std::string p): url(u), login(l), password(p) {};
    std::string url;
    std::string login;
    std::string password;
};

typedef std::vector<PasswordRecord> Records;

class PasswordRetriever {
public:

    enum ErrorCodes {
        OK = 0,
        CANNOT_OPEN_DB,
        CANNOT_RETRIEVE
    };

    PasswordRetriever(const std::string pathToFile);
    Records getPasswordRecords();
    Records::const_iterator begin();
    Records::const_iterator end() {return _records.end();};
    inline ErrorCodes errorCode() {return _errorCode;};
    inline int sqlErrorCode() {return _sqliteErrorCode;};
    inline bool operator!() {return !_isLoaded;};
    bool isDBLocked();
    std::string getSqliteErrorMessage();

protected:
    bool _isLoaded;
    ErrorCodes  _errorCode;
    int _sqliteErrorCode;
    std::string _sqliteErrorMessage;
    std::string _pathToFile;
    std::vector<PasswordRecord> _records;
    void retrieveRecords();
};



#endif // PASSWORD_RETRIEVER_H_INCLUDED
