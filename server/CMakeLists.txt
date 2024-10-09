add_executable(server
  begonia.cpp
  configuration.cpp
)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(server PUBLIC shared)