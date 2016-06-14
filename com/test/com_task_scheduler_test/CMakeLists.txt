SET(EXECUTABLE_NAME com_task_scheduler_test)

FILE(GLOB _SOURCES *.cpp)
FILE(GLOB _HEADERS *.h)
SOURCE_GROUP("Header Files" FILES ${_HEADERS})

ADD_EXECUTABLE(${EXECUTABLE_NAME} ${_SOURCES} ${_HEADERS})

SET(_LIBS ${_LIBS} "boost_system")
SET(_LIBS ${_LIBS} "pthread")
SET(_LIBS ${_LIBS} "boost_thread")
SET(_LIBS ${_LIBS} "boost_date_time")

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} com ${_LIBS})
