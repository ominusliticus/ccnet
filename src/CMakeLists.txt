file(GLOB_RECURSE SOURCE_FILES *.cpp)
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
set(CCNet_SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)

