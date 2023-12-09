add_executable(Day23 "Day23.cpp" "Day23.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
