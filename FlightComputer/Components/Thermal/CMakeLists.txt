set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ThermalTypes.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ThermalPorts.fpp"
)

register_fprime_module()

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ThermalManager")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ThermalControlLoop")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ThermalIO")

