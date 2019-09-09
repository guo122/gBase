
set(PROJECT_NAME gBase)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

set(INCROOT ${CMAKE_ROOT_DIR}/include/gBase)
set(SRCROOT ${CMAKE_ROOT_DIR}/src)

set(DIR_SRCS 
	${INCROOT}/defines.h
	${INCROOT}/config.h
	${INCROOT}/platform.h
	${INCROOT}/gBase.h
	${INCROOT}/gXml.h
	${SRCROOT}/gXml.cpp
	${INCROOT}/gCKK.h
    ${SRCROOT}/gCKK.cpp
    ${INCROOT}/gDB.h
    ${SRCROOT}/gDB.cpp
    ${INCROOT}/gSqlite.h
    ${SRCROOT}/gSqlite.cpp
    ${INCROOT}/gTime.h
    ${SRCROOT}/gTime.cpp
	${INCROOT}/gList.h
	${SRCROOT}/gList.cpp
)

set(INC_DIR 
    ${CMAKE_ROOT_DIR}/include/gBase
    ${CMAKE_ROOT_DIR}/../sqlite3
)

include_directories(${INC_DIR})

add_library_macro(
	${PROJECT_NAME} 
	SOURCES ${DIR_SRCS}
)
