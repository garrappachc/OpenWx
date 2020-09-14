#ifndef DATAREF_H
#define DATAREF_H

#include "datarefstore.h"
#include <XPLMDataAccess.h>

template<typename T>
class DataRef {
public:
    DataRef(const std::string& name) :
        m_name(name),
        m_dataRef(DataRefStore::dataRef(name))
    {

    }

    bool isValid() const
    {
        return m_dataRef;
    }

    T get();
    operator T() { return get(); }

private:
    std::string m_name;
    XPLMDataRef m_dataRef;

};

template<>
inline int DataRef<int>::get()
{
    return XPLMGetDatai(m_dataRef);
}

template<>
inline float DataRef<float>::get()
{
    return XPLMGetDataf(m_dataRef);
}

template<>
inline double DataRef<double>::get()
{
    return XPLMGetDatad(m_dataRef);
}

#endif // DATAREF_H
