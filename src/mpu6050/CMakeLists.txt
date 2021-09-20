set(TARGET_NAME mpu6050)

file(GLOB CPP
  *.cpp
)

add_library(${TARGET_NAME} ${CPP})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} pico_stdlib hardware_i2c)