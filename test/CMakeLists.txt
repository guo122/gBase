
set(PROJECT_NAME test)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

set(SRCROOT ${CMAKE_ROOT_DIR}/test)

set(DIR_SRCS 
	${SRCROOT}/gtest_main.cc
	${SRCROOT}/gXml_test.cpp
)

set(INC_DIR 
    ${CMAKE_ROOT_DIR}/3rd/googletest/googletest/include
    ${CMAKE_ROOT_DIR}/include
)

if(${THE_PROJECT_PREFIX}_OS_MACOS)
	set(LNK_DIR
		${CMAKE_ROOT_DIR}/3rd/googletest/lib/macos
	)
elseif(${THE_PROJECT_PREFIX}_OS_WINDOWS)
	set(LNK_DIR
		${CMAKE_ROOT_DIR}/3rd/googletest/lib/win64
	)
endif()

set(LNK_LIB
	gtest
	gzyBase
)

include_directories(${INC_DIR})
link_directories(${LNK_DIR})
link_libraries(${LNK_LIB})

add_executable_macro(
	${PROJECT_NAME} 
	FOLDER "test" 
	SOURCES ${DIR_SRCS}
)
