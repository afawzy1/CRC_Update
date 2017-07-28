# Set the project name
project (Std_lib)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::Std_lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/inc
)
