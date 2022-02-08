cmake_minimum_required(VERSION 3.16.3)

project (ContainerizedAppWithBOM VERSION 0.1.0 LANGUAGES CXX )

find_package (Protobuf 3.6.1 REQUIRED)
if (${Protobuf_FOUND})
  message(STATUS "Found Protobuf includes in ${Protobuf_INCLUDE_DIRS} " )
  include_directories (${Protobuf_INCLUDE_DIRS})
endif ()

add_subdirectory(src)
