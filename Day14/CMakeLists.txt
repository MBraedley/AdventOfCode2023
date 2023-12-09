add_executable(Day14 "Day14.cpp" "Day14.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
