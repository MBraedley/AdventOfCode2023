add_executable(Day08 "Day08.cpp" "Day08.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
