
cmake_minimum_required(VERSION 2.8)

project(ledramp C)

set(AVR_MCU atmega168p)

# enable_testing()
add_subdirectory(avr)
add_subdirectory(pc)
