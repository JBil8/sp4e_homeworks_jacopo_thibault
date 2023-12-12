
cmake_minimum_required (VERSION 3.1)
project (Particles)

set(CMAKE_CXX_STANDARD 14)

################################################################
# libpart
################################################################

add_library(part
  compute_boundary.cc
  compute_verlet_integration.cc 
  particle.cc 
  planet.cc
  compute_gravity.cc 
  csv_reader.cc 
  particles_factory_interface.cc 
  planets_factory.cc 
  compute_contact.cc 
  compute_kinetic_energy.cc 
  csv_writer.cc 
  system.cc 
  compute_energy.cc 
  compute_potential_energy.cc 
  ping_pong_ball.cc
  material_point.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc
  compute_temperature.cc
  material_points_factory.cc 
  )


################################################################
# Check for FFTW lib
################################################################


option(ENABLE_FFT "Enable FFT support" ON)
if(ENABLE_FFT)
message(STATUS "Searching for FFTW3 library. If something goes wrong, try specifying the CMake variable FFTW_USER_PATH.")

if(FFTW_USER_PATH)
set(FFTW_PATH ${FFTW_USER_PATH})
else(FFTW_USER_PATH)
set(FFTW_PATH /usr/local)
endif(FFTW_USER_PATH)

# Look for the library (includes and .so/.a)
# headers
find_file(FFTW_H fftw3.h ${FFTW_PATH}/include)
get_filename_component(FFTW_INCLUDES ${FFTW_H} DIRECTORY)
if(FFTW_INCLUDES)
    message(STATUS "fftw3.h found in ${FFTW_INCLUDES}")
endif(FFTW_INCLUDES)
include_directories(${FFTW_INCLUDES})
# library
find_library(FFTW_LIB libfftw3.a ${FFTW_PATH}/lib)
if(FFTW_LIB)
    message(STATUS "Library found in ${FFTW_LIB}")
endif(FFTW_LIB)

# Add executable and link it
add_executable(particles main.cc)
target_link_libraries(particles part ${FFTW_LIB})

else(ENABLE_FFT)
message(FATAL_ERROR "FFTW is required for this project.")
endif()

################################################################
# Google test
################################################################

if(EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
  add_subdirectory(googletest)
  add_executable(test_kepler test_kepler.cc)
  add_executable(test_fft test_fft.cc)
  add_executable(test_temperature test_temperature.cc)
  target_link_libraries(test_kepler part gtest_main gtest pthread )
  target_link_libraries(test_temperature part gtest_main gtest pthread ${FFTW_LIB} )
  target_link_libraries(test_fft part gtest_main gtest pthread ${FFTW_LIB})
  add_custom_target(test ./test_kepler && ./test_fft && ./test_temperature DEPENDS part test_kepler test_fft test_temperature)
else()
  message(FATAL_ERROR "
    *********************************************
    google tests is missing. 
    Did you forget `git submodule update --init`
    *********************************************
")
endif()
################################################################
# Doxygen
################################################################

find_package(Doxygen)
if (DOXYGEN_FOUND)

  # to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
  set(DOXYGEN_EXCLUDE_PATTERNS */googletest/*)

  doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
    )
  add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)
