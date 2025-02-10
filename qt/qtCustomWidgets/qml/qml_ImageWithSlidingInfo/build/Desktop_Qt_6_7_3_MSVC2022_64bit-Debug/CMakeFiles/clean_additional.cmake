# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appImageWithSlidingInfo_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appImageWithSlidingInfo_autogen.dir\\ParseCache.txt"
  "appImageWithSlidingInfo_autogen"
  )
endif()
