add_executable(Day12 "Day12.cpp" "Day12.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
