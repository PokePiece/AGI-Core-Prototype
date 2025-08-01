cmake_minimum_required(VERSION 3.16)

project(AGI_Core LANGUAGES C)

add_executable(AGI_Core main.c)

include(GNUInstallDirs)
install(TARGETS AGI_Core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
