project(cppseries)
# Gather all source files in the project directory
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cc)
#file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")

foreach(f ${SOURCES})
  message(STATUS ${f})
  get_filename_component(basename ${f} NAME_WE)
  get_filename_component(dir ${f} DIRECTORY)
endforeach()

# Create an executable with all the source files
add_executable(cppseries ${SOURCES})
