add_executable(Day18 "Day18.cpp" "Day18.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
