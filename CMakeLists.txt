
cmake_minimum_required(VERSION 3.1...3.16)

project(ledramp C)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(UNITY_ROOT /home/pimi/tools/unity-master)


set(AVR_MCU atmega168)

add_subdirectory(avr)

# enable_testing()

# add_subdirectory(test_uCunit)
# add_subdirectory(test_unity)
add_subdirectory(pc_simul)
