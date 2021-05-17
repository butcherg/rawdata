
cmake_minimum_required(VERSION 3.20)
include(FindPkgConfig)

project (rawdata)

#Logic to allow command-line specification of include directories and library paths to subsume
#the search for system libraries.  -DXXX_INCLUDES=[path] and -DXX_LIBS=[path] invoke that logic.
#If other paths or -l parameters need to be included, they are added to make the value a semicolon-
#separated list; don't include -l as cmake will add the appropriate switch.
if (DEFINED CACHE{LIBRAW_INCLUDES})
	if (DEFINED CACHE{LIBRAW_LIBS})
		set(LIBRAW_INCLUDE_DIRS ${LIBRAW_INCLUDES})
		set(LIBRAW_LIBRARIES ${LIBRAW_LIBS})
		message(STATUS "Libraw: Using user-specified libraries...")
	else()
		message(FATAL_ERROR "Need both LIBRAW_LIBS and LIBRAW_INCLUDES to bypass pkg-config")
	endif()
else()
	pkg_check_modules(LIBRAW REQUIRED libraw)
endif()

if (DEFINED CACHE{TIFF_INCLUDES})
	if (DEFINED CACHE{TIFF_LIBS})
		set(TIFF_INCLUDE_DIRS ${TIFF_INCLUDES})
		set(TIFF_LIBRARIES ${TIFF_LIBS})
		message(STATUS "TIFF: Using user-specified libraries...")
	else()
		message(FATAL_ERROR "Need both TIFF_LIBRARIES and TIFF_INCLUDES to bypass pkg-config")
	endif()
else()
	pkg_check_modules(TIFF libtiff-4)
endif()

add_executable(raw2tiff raw2tiff.cpp)
add_executable(raw2dat raw2dat.cpp)
add_executable(reallyraw2dat reallyraw2dat.cpp)

target_include_directories(raw2tiff SYSTEM PUBLIC ${LIBRAW_INCLUDE_DIRS} SYSTEM PUBLIC ${TIFF_INCLUDE_DIRS})
target_link_libraries(raw2tiff ${LIBRAW_LIBRARIES} ${TIFF_LIBRARIES})

target_include_directories(raw2dat SYSTEM PUBLIC ${LIBRAW_INCLUDE_DIRS})
target_link_libraries(raw2dat ${LIBRAW_LIBRARIES})

target_include_directories(reallyraw2dat SYSTEM PUBLIC ${LIBRAW_INCLUDE_DIRS})
target_link_libraries(reallyraw2dat ${LIBRAW_LIBRARIES})

