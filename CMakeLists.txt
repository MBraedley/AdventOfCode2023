# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AdventOfCode2023")

add_subdirectory("Day01")

add_subdirectory("Day02")

add_subdirectory("Day03")

add_subdirectory("Day04")

add_subdirectory("Day05")

add_subdirectory("Day06")

add_subdirectory("Day07")

add_subdirectory("Day08")

add_subdirectory("Day09")

add_subdirectory("Day10")

add_subdirectory("Day11")

add_subdirectory("Day12")

add_subdirectory("Day13")

add_subdirectory("Day14")

add_subdirectory("Day15")

add_subdirectory("Day16")

add_subdirectory("Day17")

add_subdirectory("Day18")

add_subdirectory("Day19")

add_subdirectory("Day20")

add_subdirectory("Day21")

add_subdirectory("Day22")

add_subdirectory("Day23")

add_subdirectory("Day24")

add_subdirectory("Day25")
