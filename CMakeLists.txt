cmake_minimum_required (VERSION 2.8.11)

project (rawdata)

pkg_search_module(libraw)
find_package(TIFF)

add_executable(raw2tiff raw2tiff.cpp)
add_executable(raw2dat raw2dat.cpp)
add_executable(reallyraw2dat reallyraw2dat.cpp)

target_link_libraries(raw2tiff ${LIBRAW_LIB} ${TIFF_LIB})
target_link_libraries(raw2dat ${LIBRAW_LIB})
target_link_libraries(reallyraw2dat ${LIBRAW_LIB})