# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Waze_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Waze_autogen.dir\\ParseCache.txt"
  "Waze_autogen"
  )
endif()
