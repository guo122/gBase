
set(PROJECT_NAME gzyBase)

set(INCROOT ${CMAKE_ROOT_DIR}/include/gzyBase)
set(SRCROOT ${CMAKE_ROOT_DIR}/src)

set(DIR_SRCS 
			${INCROOT}/gXml.h
			${SRCROOT}/gXml.cpp
)

set(INC_DIR 
    ${CMAKE_ROOT_DIR}/include/gzyBase
)

include_directories(${INC_DIR})

add_library_macro(
	${PROJECT_NAME} 
	FOLDER "libs" 
	SOURCES ${DIR_SRCS}
)
