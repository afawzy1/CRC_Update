# Set the project name
project (SParser_lib)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/SParser.c
)

# Add a library with the above sources
add_library(${PROJECT_NAME} ${SOURCES})
add_library(sub::SParser_lib ALIAS ${PROJECT_NAME})

include_directories( ${PROJECT_NAME}
    PUBLIC 
	${Std_lib_SOURCE_DIR}/inc
	${PROJECT_SOURCE_DIR}/inc
)
