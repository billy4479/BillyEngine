if(CMAKE_CROSSCOMPILING)
    find_package(Gen)
else()
    add_subdirectory(Generator)
endif()
file(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/Resources/*)

set(BE_GENERATED_DIR "Generated")
set(BE_GENERATED_BUNDLE_DIR "${BE_GENERATED_DIR}/Bundled")

foreach(resource ${RESOURCES})
    get_filename_component(resource_name ${resource} NAME)
    string(REPLACE "." "_" resource_header_name ${resource_name})
    set(generated_resource_path "${BE_GENERATED_BUNDLE_DIR}/${resource_header_name}.hpp")
    list(APPEND BE_GENERATED_FILES ${generated_resource_path})
    
    add_custom_command(
        OUTPUT ${generated_resource_path}
        COMMAND Generator bundler Generated ${resource}
        DEPENDS ${resource}
        DEPENDS Generator
    )
endforeach()

add_custom_command(
    OUTPUT ${BE_GENERATED_BUNDLE_DIR}/Types.hpp
    COMMAND Generator bundler-types Generated
    DEPENDS Generator
)
list(APPEND BE_GENERATED_FILES ${BE_GENERATED_BUNDLE_DIR}/Types.hpp)

add_custom_target(GenerateAll DEPENDS ${BE_GENERATED_FILES})
