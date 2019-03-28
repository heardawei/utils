include(ExternalProject)

ExternalProject_Add(libuuid
    PREFIX libuuid-prefix
    # DOWNLOAD_DIR libuuid-download
    # SOURCE_DIR libuuid-source
    DOWNLOAD_COMMAND tar zxf ${PROJECT_SOURCE_DIR}/libuuid-1.0.3.tar.gz
    CONFIGURE_COMMAND <DOWNLOAD_DIR>/libuuid-1.0.3/configure
    BUILD_COMMAND ${MAKE}
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/lib/ && cp <SOURCE_DIR>/.libs/libuuid.a <SOURCE_DIR>/.libs/libuuid.so <SOURCE_DIR>/.libs/libuuid.so.1 <SOURCE_DIR>/.libs/libuuid.so.1.0.0 ${PROJECT_SOURCE_DIR}/lib/
    LOG_DOWNLOAD 1
    LOG_BUILD 1
    # LOG_INSTALL 1
)

