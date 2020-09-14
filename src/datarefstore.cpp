#include "datarefstore.h"

std::map<std::string, XPLMDataRef> DataRefStore::m_dataRefs;

XPLMDataRef DataRefStore::dataRef(const std::string& dataRefName)
{
    if (m_dataRefs.count(dataRefName) == 0) {
        XPLMDataRef dataRef = XPLMFindDataRef(dataRefName.c_str());
        if (dataRef)
            m_dataRefs.emplace(dataRefName, dataRef);
    }

    return m_dataRefs[dataRefName];
}

void DataRefStore::clear()
{
    m_dataRefs.clear();
}
