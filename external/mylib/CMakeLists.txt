cmake_minimum_required(VERSION 3.20)
project(rust-c-playground VERSION 0.1.0 LANGUAGES C)

include(GNUInstallDirs)

add_library(mylib src/mylib.c)
target_include_directories(mylib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
set_target_properties(mylib
  PROPERTIES
    PUBLIC_HEADER include/mylib.h
    DEBUG_POSTFIX -d
)

install(TARGETS mylib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

include(CPack)
