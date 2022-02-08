protobuf_generate_cpp (MsgSrc MsgHdrs ${CMAKE_CURRENT_SOURCE_DIR}/Msg.proto )


add_executable (main
  main.cpp
  ${MsgSrc}
)

#Include build directory with generated protobuf header file 
target_include_directories(main 
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(main 
  PRIVATE ${Protobuf_LIBRARIES}
  PRIVATE MPI::MPI_CXX
)

