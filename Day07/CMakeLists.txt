add_executable(Day07 "Day07.cpp" "Day07.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
