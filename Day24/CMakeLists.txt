add_executable(Day24 "Day24.cpp" "Day24.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
