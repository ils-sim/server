
FILE(GLOB _SOURCES *.cpp)
FILE(GLOB _HEADERS *.h)
SOURCE_GROUP("Header Files" FILES ${_HEADERS})

ADD_EXECUTABLE(Sync ${_SOURCES} ${_HEADERS})

SET(_LIBS ${_LIBS} "protobuf")
SET(_LIBS ${_LIBS} "protoc")
SET(_LIBS ${_LIBS} "boost_system")

TARGET_LINK_LIBRARIES(Sync com ${_LIBS} Threads::Threads)
