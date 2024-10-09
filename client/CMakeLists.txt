add_executable(client
  begonia.cpp
  configuration.cpp
)

target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(client PUBLIC shared)