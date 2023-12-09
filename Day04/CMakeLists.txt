add_executable(Day04 "Day04.cpp" "Day04.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
