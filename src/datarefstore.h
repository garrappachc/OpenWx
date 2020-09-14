#ifndef DATAREFSTORE_H
#define DATAREFSTORE_H

#include <XPLMDataAccess.h>
#include <map>
#include <string>

class DataRefStore {
public:
    static XPLMDataRef dataRef(const std::string& dataRefName);

    static void clear();

private:
    static std::map<std::string, XPLMDataRef> m_dataRefs;

};

#endif // DATAREFSTORE_H
