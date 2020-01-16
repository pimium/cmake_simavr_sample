
cmake_minimum_required(VERSION 2.8)

set(exe_file "${PROJECT_NAME}-x86_64-linux-gnu.exe")
set(avr_file "avr/${PROJECT_NAME}-${AVR_MCU}.elf")

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

include_directories(
  /usr/local/include/simavr/
  /usr/local/include/simavr/avr/
  /usr/include/libdrm
  /usr/include/GL/
  parts/
)

add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Wno-unused-parameter)
add_definitions(-Wno-unused-result)
add_definitions(-Wno-missing-field-initializers)
add_definitions(-Wno-sign-compare)
add_definitions(-g)

add_subdirectory(cores)
add_subdirectory(parts)

add_executable(
    ${exe_file}
    ledramp.c
)

set_target_properties(
      ${exe_file}
      PROPERTIES
        COMPILE_FLAGS "--std=gnu99 -Wall -MMD"
        LINK_FLAGS "-lGL -lGLU -lglut -lpthread -lsimavr -lm -lelf"
)

target_link_libraries(${exe_file} cores parts)


add_custom_command(
        OUTPUT simulation
        COMMAND ${exe_file} "avr/${PROJECT_NAME}-${AVR_MCU}.elf"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS ${avr_file}
)

add_custom_target(
        run_simulation
        ALL
        WORKING_DIRECTORY CMAKE_BINARY_DIR
        DEPENDS simulation
)

set_target_properties(
        run_simulation
        PROPERTIES
        OUTPUT_NAME run_simulation
)
