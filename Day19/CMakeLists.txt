add_executable(Day19 "Day19.cpp" "Day19.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
