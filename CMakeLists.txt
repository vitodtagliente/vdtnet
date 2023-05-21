cmake_minimum_required(VERSION 3.2)
if(TARGET vdtnet)
	return()
endif()
project(vdtnet)

set(CMAKE_CXX_STANDARD 17)

if(ASAN_ENABLED)
	string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")
	add_compile_options(-fsanitize=address -fsanitize=fuzzer)
endif()

file(GLOB_RECURSE PROJECT_HEADERS "include/vdtnet/*.h") 
file(GLOB_RECURSE PROJECT_SOURCES "source/*.cpp")

foreach(_source IN ITEMS ${PROJECT_HEADERS})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${PROJECT_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_library(
    ${PROJECT_NAME} 
	STATIC
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES} 
)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()


target_include_directories(${PROJECT_NAME} PUBLIC include)