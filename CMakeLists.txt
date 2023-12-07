cmake_minimum_required(VERSION 3.14)

project(
	FileReadTest VERSION 1.0
	LANGUAGES C CXX
)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "")

add_subdirectory(benchmark)

add_executable(BenchFile "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(BenchFile PRIVATE benchmark::benchmark)
set_target_properties(BenchFile PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
