set (grib_HEADERS
    grib.h
)

set (grib_SOURCES
    grib.cpp
)

add_library (grib OBJECT
    ${grib_HEADERS}
    ${grib_SOURCES}
)

add_executable (gribtest gribtest.c)
target_link_libraries (gribtest g2c)
