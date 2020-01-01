set(LIBRARY_NAME cores)
set(lib_file "${LIBRARY_NAME}")

include_directories(
  /usr/local/include/simavr/
  /usr/local/include/simavr/avr/
  /usr/include/libdrm
  /usr/lib/avr/include/
)

add_library(
   ${lib_file}
   sim_mega168.c 
)

set_target_properties(
    ${lib_file}
    PROPERTIES
    COMPILE_FLAGS "--std=gnu99 -Wall"
    OUTPUT_NAME "${lib_file}"
)

if(NOT TARGET ${LIBRARY_NAME})
    add_custom_target(
        ${LIBRARY_NAME}
        ALL
        DEPENDS ${lib_file}
    )

    set_target_properties(
        ${LIBRARY_NAME}
        PROPERTIES
        OUTPUT_NAME "${lib_file}"
    )
endif(NOT TARGET ${LIBRARY_NAME})
