add_executable(Day01 "Day01.cpp" "Day01.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()