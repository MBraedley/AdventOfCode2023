﻿add_executable(Day05 "Day05.cpp" "Day05.h")
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
	message("Copying input file")
	configure_file("input.txt" "./input.txt" COPYONLY)
else()
	message(WARNING "Input file not found")
endif()
