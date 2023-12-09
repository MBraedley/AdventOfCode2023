add_executable(Day20 "Day20.cpp" "Day20.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
