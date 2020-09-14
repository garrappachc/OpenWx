add_library (g2c STATIC
    gridtemplates.c
    drstemplates.c
    pdstemplates.c
    gbits.c
    g2_unpack1.c
    g2_unpack2.c
    g2_unpack3.c
    g2_unpack4.c
    g2_unpack5.c
    g2_unpack6.c
    g2_unpack7.c
    g2_free.c
    g2_info.c
    g2_getfld.c
    simunpack.c
    comunpack.c
    pack_gp.c
    reduce.c
    specpack.c
    specunpack.c
    rdieee.c
    mkieee.c
    int_power.c
    simpack.c
    compack.c
    cmplxpack.c
    misspack.c
    jpcpack.c
    jpcunpack.c
    pngpack.c
    pngunpack.c
    dec_jpeg2000.c
    enc_jpeg2000.c
    dec_png.c
    enc_png.c
    g2_create.c
    g2_addlocal.c
    g2_addgrid.c
    g2_addfield.c
    g2_gribend.c
    getdim.c
    g2_miss.c
    getpoly.c
    seekgb.c
)

target_compile_definitions (g2c PRIVATE __64BIT__)

target_compile_options (g2c
    PRIVATE
        -Wno-format
        -Wno-pointer-sign
)

set_target_properties (g2c PROPERTIES
    VERSION 1.6.0
)

target_include_directories (g2c
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries (g2c
    PUBLIC
        m
)
