add_executable(Day11 "Day11.cpp" "Day11.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
