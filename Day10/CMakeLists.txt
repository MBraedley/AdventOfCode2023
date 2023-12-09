add_executable(Day10 "Day10.cpp" "Day10.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
