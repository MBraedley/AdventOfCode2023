add_executable(Day03 "Day03.cpp" "Day03.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
