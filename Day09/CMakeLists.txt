add_executable(Day09 "Day09.cpp" "Day09.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
