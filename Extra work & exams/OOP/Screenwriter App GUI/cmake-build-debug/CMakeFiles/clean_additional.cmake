# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Screenwriter_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Screenwriter_autogen.dir\\ParseCache.txt"
  "Screenwriter_autogen"
  )
endif()
