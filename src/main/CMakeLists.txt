set(TARGET_NAME main)

file(GLOB CPP
  *.cpp
)

add_executable(${TARGET_NAME} ${CPP})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
pico_add_extra_outputs(${TARGET_NAME})
target_link_libraries(${TARGET_NAME} pico_stdlib)
