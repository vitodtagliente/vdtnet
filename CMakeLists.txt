cmake_minimum_required(VERSION 3.2)
project(vdtnet)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB PROJECT_HEADERS "include/vdtnet/*.h") 
file(GLOB PROJECT_SOURCES "source/*.cpp")

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_library(
    ${PROJECT_NAME} 
	STATIC
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES} 
)