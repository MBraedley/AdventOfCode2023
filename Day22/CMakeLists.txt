add_executable(Day22 "Day22.cpp" "Day22.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
