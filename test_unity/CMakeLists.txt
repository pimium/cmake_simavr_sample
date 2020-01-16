# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.16)

find_package(ruby 2.3.0)

Message(${RUBY_EXECUTABLE})

include_directories(
    . 
    ${UNITY_ROOT}/src/
    ../test_include
)

add_custom_command(
    OUTPUT always_rebuild
    COMMAND cmake -E echo
)

add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/test_runners/TestProductionCode_Runner.c"
    COMMAND "${RUBY_EXECUTABLE}" "${UNITY_ROOT}/auto/generate_test_runner.rb" "${CMAKE_CURRENT_SOURCE_DIR}/TestProductionCode.c" "${CMAKE_CURRENT_SOURCE_DIR}/test_runners/TestProductionCode_Runner.c" --argument
    DEPENDS always_rebuild
)

# add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/test_runners/TestProductionCode2_Runner.c"
#     COMMAND "${RUBY_EXECUTABLE}" "${UNITY_ROOT}/auto/generate_test_runner.rb" "${CMAKE_CURRENT_SOURCE_DIR}/TestProductionCode2.c" "${CMAKE_CURRENT_SOURCE_DIR}/test_runners/TestProductionCode2_Runner.c" --argument
#     DEPENDS always_rebuild
# )

add_custom_target(generate_test_runner ALL
)
  
add_custom_target(run_test ALL
    COMMAND test_1 --argument
    # COMMAND test_2 --argument
    DEPENDS generate_test_runner
)
# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/test_runners/TestProductionCode_Runner.c DESTINATION test_runners)

# Adding something we can run - Output name matches target name
add_executable(test_1 
    ${PROJECT_SOURCE_DIR}/avr/ledramp_avr.c
    TestProductionCode.c
    test_runners/TestProductionCode_Runner.c
    ${UNITY_ROOT}/src/unity.c
)

# add_executable(test_2 
#     TestProductionCode2.c
#     test_runners/TestProductionCode2_Runner.c
#     ${UNITY_ROOT}/src/unity.c
# )

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
# target_link_libraries(test_1 PRIVATE ProductionCode)
# target_link_libraries(test_2 PRIVATE ProductionCode2)