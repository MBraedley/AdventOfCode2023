add_executable(Day02 "Day02.cpp" "Day02.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
