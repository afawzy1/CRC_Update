# Set the project name
project (crc_lib)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/CRC.c
)

# Add a library with the above sources
add_library(${PROJECT_NAME} ${SOURCES})
add_library(sub::crc_lib ALIAS ${PROJECT_NAME})

include_directories( ${PROJECT_NAME}
    PUBLIC 
	${SParser_lib_SOURCE_DIR}/inc
	${Std_lib_SOURCE_DIR}/inc
	${PROJECT_SOURCE_DIR}/inc
)
