
FILE(GLOB_RECURSE PROJECT_SOURCE_FILES "${PROJECT_SOURCE}/*.h" "${PROJECT_SOURCE}/*.cpp" "${PROJECT_SOURCE}/*.templ")

MACRO(GroupSources curdir)
	FILE(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)
	FOREACH(child ${children})
		IF(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			GroupSources(${curdir}/${child})
		ELSE()
			STRING(REPLACE "/" "\\" groupname ${curdir})
			# I would like to call the src root folder in a different name, only in visual studio (not mandatory requirement)
			#STRING(REPLACE "src" "Common" groupname ${groupname})
			SOURCE_GROUP(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
		ENDIF()
	ENDFOREACH()
ENDMACRO()

GroupSources(src)
ADD_LIBRARY(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} protocol)

