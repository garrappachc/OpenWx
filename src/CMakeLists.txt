find_package (CURL REQUIRED)

add_subdirectory (grib)

set (openwx_HEADERS
    dataref.h
    datarefstore.h
    httpclient.h
    metarquerywindow.h
    window.h
)

set (openwx_SOURCES
    dataref.cpp
    datarefstore.cpp
    httpclient.cpp
    metarquerywindow.cpp
    window.cpp
)

add_library (openwx MODULE
    ${openwx_HEADERS}
    ${openwx_SOURCES}
    $<TARGET_OBJECTS:grib>
    main.cpp
)

target_link_libraries (openwx
    PUBLIC
        CURL::libcurl
    PRIVATE
        g2c
)

target_include_directories (openwx PUBLIC ${XPLANE_SDK_PATH}/CHeaders/XPLM)
target_compile_definitions (openwx PUBLIC
    XPLM200=1
    XPLM210=1
    XPLM300=1
    XPLM301=1
    LIN=1
)

set_target_properties (openwx PROPERTIES
    PREFIX ""
    SUFFIX ""
    OUTPUT_NAME lin.xpl
)
