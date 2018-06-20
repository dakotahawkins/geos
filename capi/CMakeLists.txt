#################################################################################
#
# GEOS C library build configuration for CMake build system
#
# Copyright (C) 2009 Mateusz Loskot <mateusz@loskot.net>
#
# This is free software; you can redistribute and/or modify it under
# the terms of the GNU Lesser General Public Licence as published
# by the Free Software Foundation. 
# See the COPYING file for more information.
#
#################################################################################

if(WIN32 AND BUILD_SHARED_LIBS)
    add_definitions("-DGEOS_DLL_EXPORT=1")
endif()

set(geos_c_SOURCES
  geos_c.cpp
  geos_ts_c.cpp)

file(GLOB geos_capi_HEADERS ${CMAKE_BINARY_DIR}/capi/*.h) # fix source_group issue

if(NOT GEOS_ENABLE_MACOSX_FRAMEWORK AND BUILD_SHARED_LIBS)
  set(GEOS_TARGET_NAME geos)

  # if building OS X framework or only building static libs, CAPI built into C++ library
  add_library(${GEOS_TARGET_NAME} ${geos_c_SOURCES})

  target_link_libraries(${GEOS_TARGET_NAME} geos_cpp)

  if (WIN32)
    set_target_properties(${GEOS_TARGET_NAME}
      PROPERTIES
      VERSION ${CAPI_VERSION}
      CLEAN_DIRECT_OUTPUT 1)
  else()
    set_target_properties(${GEOS_TARGET_NAME}
      PROPERTIES
      VERSION ${CAPI_VERSION}
      SOVERSION ${CAPI_SOVERSION}
      CLEAN_DIRECT_OUTPUT 1)
  endif()

  if(WIN32)
    set(geos_config_dir "cmake")
  else()
    set(geos_config_dir "${CMAKE_INSTALL_LIBDIR}/cmake/GEOS")
  endif()

  install(TARGETS ${GEOS_TARGET_NAME}
    EXPORT ${GEOS_TARGET_NAME}ConfigInternal
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT "runtime"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

  install(EXPORT ${GEOS_TARGET_NAME}ConfigInternal
    DESTINATION "${geos_config_dir}"
    NAMESPACE "geos_"
    COMPONENT "development")

endif()

#################################################################################
# Installation
#################################################################################

include(GNUInstallDirs)
if(APPLE AND GEOS_ENABLE_MACOSX_FRAMEWORK)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/geos_c.h
    DESTINATION GEOS.framework/Versions/${VERSION_MAJOR}/Headers)
  install(CODE "execute_process(COMMAND sed -E -i \"\" \"s,# *include[[:space:]]+<geos/,#include <GEOS/,g\" \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/GEOS.framework/Versions/${VERSION_MAJOR}/Headers/geos_c.h\")")
else()
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/geos_c.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()

#################################################################################
# Group source files for IDE source explorers (e.g. Visual Studio)
#################################################################################

source_group("Header Files" FILES ${geos_capi_HEADERS})
