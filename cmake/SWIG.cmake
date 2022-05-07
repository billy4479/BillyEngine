if(GENERATE_BINDINGS)
    find_package(SWIG)
    include(UseSWIG)

    file(GLOB_RECURSE SWIG_SRC swig/*.i)
    set_property(SOURCE ${SWIG_SRC} PROPERTY CPLUSPLUS ON)
    set_property(SOURCE ${SWIG_SRC} PROPERTY USE_TARGET_INCLUDE_DIRECTORIES ON)
    
    swig_add_library(
        ${PROJECT_NAME}_swig
        LANGUAGE CSharp
        OUTPUT_DIR Bindings
        SOURCES ${SWIG_SRC} $<TARGET_OBJECTS:${PROJECT_NAME}_objs>
    )

    target_include_directories(
        ${PROJECT_NAME}_swig
        PRIVATE include include/BillyEngine
    )
endif()
