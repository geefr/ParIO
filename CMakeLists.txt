include(CheckIncludeFile)

# Could probably work with less
cmake_minimum_required( VERSION 3.2 )

set( PARIO_VERSION_MAJOR 1 )
set( PARIO_VERSION_MINOR 0 )
set( PARIO_VERSION_PATCH 0 )
set( PARIO_VERSION_STRING ${PARIO_VERSION_MAJOR}.${PARIO_VERSION_MINOR}.${PARIO_VERSION_PATCH} )
set( PARIO_VERSION_ABI 1 )

project( ParIO VERSION ${PARIO_VERSION_STRING} )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
  set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "MinSizeRel" "RelWithDebInfo" )
endif()

set( LIB_TYPE SHARED CACHE STRING "The type of library to build" )
set_property( CACHE LIB_TYPE PROPERTY STRINGS "SHARED" "STATIC" )
option( BUILD_TEST "Build test executable" OFF )

check_include_file( "linux/parport.h" HAVE_LINUX_PARPORT_H )
check_include_file( "linux/ppdev.h" HAVE_LINUX_PPDEV_H )
if( NOT HAVE_LINUX_PARPORT_H )
  message( FATAL_ERROR "PPStep requires linux/parport.h" )
endif()
if( NOT HAVE_LINUX_PPDEV_H )
  message( FATAL_ERROR "PPStep requires linux/ppdev.h" )
endif()

set( CMAKE_CXX_STANDARD 11 )

set( CMAKE_CXX_FLAGS "-Werror=all" )

add_library( pario ${LIB_TYPE} pario.cpp )
set_target_properties( pario PROPERTIES VERSION ${PARIO_VERSION_STRING} SOVERSION ${PARIO_VERSION_ABI} )
install( TARGETS pario
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib )

if( BUILD_TEST )
  add_executable( pariotest main.cpp )
  target_link_libraries( pariotest pario )
endif()

