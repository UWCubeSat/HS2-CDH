####
# This sets up the build system for the 'FlightComputer' project, including
# components and deployments from project.cmake. In addition, it imports the core F Prime components.
####

cmake_minimum_required(VERSION 3.24.2)
project(FlightComputer C CXX)

###
# F' Core Setup
# This includes all of the F prime core components, and imports the make-system.
###
include("${CMAKE_CURRENT_LIST_DIR}/lib/fprime/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
fprime_setup_included_code()

include(FetchContent)

##### hyperC Compression Library ####

set(HYPERC_REPO https://github.com/MahirEmran/found_hyperC.git)
set(HYPERC_TAG found)

FetchContent_Declare(
	found_hyperc
	GIT_REPOSITORY ${HYPERC_REPO}
	GIT_TAG ${HYPERC_TAG}
)

FetchContent_MakeAvailable(found_hyperc)

if(TARGET hc-compress-lib)
	# Fix include dirs for exported target
	set_target_properties(hc-compress-lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "")
	target_include_directories(hc-compress-lib
		PUBLIC
			$<BUILD_INTERFACE:${found_hyperc_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>)
endif()


# This includes project-wide objects
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/FlightComputer")
