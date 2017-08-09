project(crc_update)

set(SOURCES
    main.c
)
set(DirectoryName bin)
# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the static library from subproject1 using it's alias sub::lib1
# Link the header only library from subproject2 using it's alias sub::lib2
target_link_libraries(${PROJECT_NAME}
    sub::crc_lib
    sub::Std_lib
	sub::SParser_lib
)

# Include the inc directories from the sub projects
include_directories( ${DirectoryName}
    PUBLIC
	${Std_lib_SOURCE_DIR}/inc
    ${crc_lib_SOURCE_DIR}/inc
	${SParser_lib_SOURCE_DIR}/inc
)
