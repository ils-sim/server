SET(EXECUTABLE_NAME com_client_test)

FILE(GLOB _SOURCES *.cpp)
FILE(GLOB _HEADERS *.h)
SOURCE_GROUP("Header Files" FILES ${_HEADERS})

ADD_EXECUTABLE(${EXECUTABLE_NAME} ${_SOURCES} ${_HEADERS})

SET(_LIBS ${_LIBS} "protobuf")
SET(_LIBS ${_LIBS} "protoc")
SET(_LIBS ${_LIBS} "boost_system")
SET(_LIBS ${_LIBS} "boost_thread")

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} com ${_LIBS} Threads::Threads)
