add_executable(Day15 "Day15.cpp" "Day15.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
