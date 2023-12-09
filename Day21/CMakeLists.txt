add_executable(Day21 "Day21.cpp" "Day21.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
