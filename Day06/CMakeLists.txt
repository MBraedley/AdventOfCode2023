add_executable(Day06 "Day06.cpp" "Day06.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
