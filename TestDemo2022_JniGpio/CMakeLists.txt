cmake_minimum_required(VERSION 3.5)

project(TestDemo2022_JniGpio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


FILE(GLOB_RECURSE PROJECT_SOURCES "src/*.h" "src/*.cpp")
add_executable(
	TestDemo2022_JniGpio
	${PROJECT_SOURCES}
)

target_link_libraries(
	TestDemo2022_JniGpio PUBLIC
	/usr/lib/libpigpio.so
)

include_directories(
	/usr/include/
	/usr/lib/jvm/java-8-openjdk-armhf/include/
	/usr/lib/jvm/java-8-openjdk-armhf/include/linux/
)
