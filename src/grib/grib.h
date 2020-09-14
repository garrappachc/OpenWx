#ifndef GRIB_GRIB_H
#define GRIB_GRIB_H

#include "../httpclient.h"

class Grib {
public:
    Grib();
    virtual ~Grib();

private:
    HttpClient m_http;

};

#endif // GRIB_GRIB_H
