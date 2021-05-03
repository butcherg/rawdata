cmake_minimum_required (VERSION 2.8.11)
include(FindPkgConfig)

project (rawdata)

pkg_check_modules(LIBRAW libraw)
find_package(TIFF)

add_executable(raw2tiff raw2tiff.cpp)
add_executable(raw2dat raw2dat.cpp)
add_executable(reallyraw2dat reallyraw2dat.cpp)

target_include_directories(raw2tiff SYSTEM PUBLIC ${LIBRAW_INCLUDE_DIRS} SYSTEM PUBLIC ${TIFF_INCLUDE_DIRS})
target_link_libraries(raw2tiff ${LIBRAW_LIBRARIES} ${TIFF_LIBRARIES})

target_include_directories(raw2dat SYSTEM PUBLIC ${LIBRAW_INCLUDE_DIRS})
target_link_libraries(raw2dat ${LIBRAW_LIBRARIES})

target_include_directories(reallyraw2dat SYSTEM PUBLIC ${LIBRAW_INCLUDE_DIRS})
target_link_libraries(reallyraw2dat ${LIBRAW_LIBRARIES})

