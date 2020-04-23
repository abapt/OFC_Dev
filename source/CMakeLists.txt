# ----------------------------------------------------------
# In include
# ----------------------------------------------------------

message( STATUS "in source/include ")
add_subdirectory(include)

# ----------------------------------------------------------
# In Src
# ----------------------------------------------------------

message( STATUS "in source/src ")
add_subdirectory(src)

# ----------------------------------------------------------
# Compilation
# ----------------------------------------------------------

message( STATUS "Build Libraries OFCpkg")
ADD_LIBRARY(OFCpkg SHARED ${OFC_SRC_FILE})
target_link_libraries(OFCpkg)
