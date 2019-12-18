#include "password_retriever.h"
#include <sqlite3.h>
#include <cstdio>
#include <iostream>
#include <fstream>

#ifndef __linux__
#include <Windows.h>
#include <WinCrypt.h>
#endif // !__linux__


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

		sqlite3_stmt *statement;
		rc = sqlite3_prepare_v2(db, sql, strlen(sql), &statement, 0);
		if (rc != SQLITE_OK) {
			_errorCode = PasswordRetriever::CANNOT_OPEN_DB;
		} else {
			int result = 0;
			while (sqlite3_step(statement) == SQLITE_ROW) {
				const char *url = (char *)sqlite3_column_text(statement, 0);
				const char *username = (char *)sqlite3_column_text(statement, 1);
				const int passwordSize = sqlite3_column_bytes(statement, 2);
				const void *encPassword = sqlite3_column_blob(statement, 2);

				#ifdef __linux__
				
				const auto password = std::string((char *encPassword), passwordSize);
				_records.emplace_back(std::string(url), std::string(username), password);

				#else
				DATA_BLOB encryptedPassword;
				encryptedPassword.cbData = passwordSize;
				encryptedPassword.pbData = (BYTE *)encPassword;
				DATA_BLOB dataVerify;
				if (CryptUnprotectData(&encryptedPassword, NULL, NULL, NULL, NULL, 0, &dataVerify)) {					
					const auto password = std::string((char *)dataVerify.pbData, dataVerify.cbData);
					std::cout << "Decrypt success" << password <<std::endl;
					_records.emplace_back(std::string(url), std::string(username), password);
				}

				#endif
			}
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
