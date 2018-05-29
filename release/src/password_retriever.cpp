#include "password_retriever.h"
#include <sqlite3.h>
#include <cstdio>
#include <iostream>
#include <fstream>

PasswordRetriever::PasswordRetriever(const std::string pathToFile): _pathToFile(pathToFile), _isLoaded(false) {
    retrieveRecords();
}

void PasswordRetriever::retrieveRecords() {
    _isLoaded = false;
    _errorCode = PasswordRetriever::OK;
    _sqliteErrorCode = 0;
    _records.clear();

    std::string tmp = std::tmpnam(nullptr);
    std::ifstream ifs(_pathToFile.c_str(), std::ios::binary);
    std::ofstream ofs(tmp, std::ios::binary);
    ofs<<ifs.rdbuf();
    ifs.close();
    ofs.close();

    sqlite3 *db;
    int rc = sqlite3_open_v2(tmp.c_str(), &db, SQLITE_OPEN_READONLY, nullptr);
    if (rc != SQLITE_OK) {
        _errorCode = PasswordRetriever::CANNOT_OPEN_DB;
    } else {
        const char* sql = "SELECT action_url, username_value, password_value FROM logins";
        char* errorMessage = nullptr;
        rc = sqlite3_exec(
            db,
            sql,
            [](void* self, int argc, char** argv, char** azColName) -> int {
                if (argc == 3) {
                    static_cast<PasswordRetriever*>(self)->_records.emplace_back(std::string(argv[0]), std::string(argv[1]), std::string(argv[2]));
                    return 0;
                }
                return 1;
            },
            this,
            &errorMessage
        );
        if (rc != SQLITE_OK) {
            _errorCode = PasswordRetriever::CANNOT_RETRIEVE;
        } else {
            _isLoaded = true;
        }
    }
    _sqliteErrorCode = rc;
    _sqliteErrorMessage = sqlite3_errmsg(db);
    sqlite3_close(db);

    std::remove(tmp.c_str());

}

std::string PasswordRetriever::getSqliteErrorMessage() {
    return _sqliteErrorMessage;
}

Records PasswordRetriever::getPasswordRecords() {
    if (!_isLoaded) {
        retrieveRecords();
    }
    return _records;
}

Records::const_iterator PasswordRetriever::begin() {
    if (!_isLoaded) {
        retrieveRecords();
    }
    return _records.begin();
};

bool PasswordRetriever::isDBLocked() {
    return _sqliteErrorCode == SQLITE_BUSY || _sqliteErrorCode == SQLITE_LOCKED;
};
