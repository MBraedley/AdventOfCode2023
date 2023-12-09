add_executable(Day13 "Day13.cpp" "Day13.h")
if (EXISTS "input.txt")
	configure_file("input.txt" "./input.txt" COPYONLY)
endif()
