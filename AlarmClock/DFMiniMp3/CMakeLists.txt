add_library(DFMiniMp3 INTERFACE)

target_sources(DFMiniMp3 INTERFACE
  "${CMAKE_CURRENT_LIST_DIR}/DFMiniMp3.h"
)

target_include_directories(DFMiniMp3 INTERFACE
 "${CMAKE_CURRENT_LIST_DIR}"
)
