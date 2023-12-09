add_executable(Day16 "Day16.cpp" "Day16.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
