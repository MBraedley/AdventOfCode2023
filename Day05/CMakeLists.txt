add_executable(Day05 "Day05.cpp" "Day05.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
