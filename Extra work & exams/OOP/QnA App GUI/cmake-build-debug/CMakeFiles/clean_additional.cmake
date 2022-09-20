# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QnA_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QnA_autogen.dir\\ParseCache.txt"
  "QnA_autogen"
  )
endif()
