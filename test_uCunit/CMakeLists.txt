# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.16)

include_directories(
    . 
    include
    ../test_include
)

# add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/test_runners/TestProductionCode_Runner.c"
#     COMMAND "${RUBY_EXECUTABLE}" "${UNITY_ROOT}/auto/generate_test_runner.rb" "${CMAKE_CURRENT_SOURCE_DIR}/TestProductionCode.c" "${CMAKE_CURRENT_SOURCE_DIR}/test_runners/TestProductionCode_Runner.c" --argument
#     DEPENDS generate_test_runner
# )

# add_custom_target(generate_test_runner ALL
# )
  
# add_custom_target(run_test_uCunit ALL
#     COMMAND test_uCunit --argument
#     DEPENDS test_uCunit
# )

add_custom_target(run_test_uCunit2 ALL
    COMMAND test_uCunit2 --argument
    DEPENDS test_uCunit2
)

# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/test_runners/TestProductionCode_Runner.c DESTINATION test_runners)

# Adding something we can run - Output name matches target name
# add_executable(test_uCunit 
#     System.c
#     Testsuite.c
# )

add_executable(test_uCunit2 
    ${PROJECT_SOURCE_DIR}/avr/ledramp_avr.c
    System.c
    second_testsuite.c
)


# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
# target_link_libraries(test_uCunit PRIVATE ProductionCode)
# target_link_libraries(test_uCunit2 PRIVATE ProductionCode)
