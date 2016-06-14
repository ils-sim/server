SET(EXECUTABLE_NAME com_sql_test)

FILE(GLOB _SOURCES *.cpp)
FILE(GLOB _HEADERS *.h)
SOURCE_GROUP("Header Files" FILES ${_HEADERS})

ADD_EXECUTABLE(${EXECUTABLE_NAME} ${_SOURCES} ${_HEADERS})

SET(_LIBS ${_LIBS} "boost_system")
SET(_LIBS ${_LIBS} "boost_date_time")
SET(_LIBS ${_LIBS} "mysqlcppconn")
SET(_LIBS ${_LIBS} "sqlite3")

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} com ${_LIBS} Threads::Threads)
