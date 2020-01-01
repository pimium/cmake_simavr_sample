set(LIBRARY_NAME parts)
set(lib_file "${LIBRARY_NAME}")

add_library(
   ${lib_file}
   button.c
   button.h 
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
