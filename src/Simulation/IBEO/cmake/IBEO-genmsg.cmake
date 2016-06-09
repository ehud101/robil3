# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "IBEO: 1 messages, 0 services")

set(MSG_I_FLAGS "-IIBEO:/home/robil/robil2/src/Simulation/IBEO/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(IBEO_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/robil/robil2/src/Simulation/IBEO/msg/MultiLaserScan.msg" NAME_WE)
add_custom_target(_IBEO_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "IBEO" "/home/robil/robil2/src/Simulation/IBEO/msg/MultiLaserScan.msg" "std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(IBEO
  "/home/robil/robil2/src/Simulation/IBEO/msg/MultiLaserScan.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/IBEO
)

### Generating Services

### Generating Module File
_generate_module_cpp(IBEO
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/IBEO
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(IBEO_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(IBEO_generate_messages IBEO_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robil/robil2/src/Simulation/IBEO/msg/MultiLaserScan.msg" NAME_WE)
add_dependencies(IBEO_generate_messages_cpp _IBEO_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(IBEO_gencpp)
add_dependencies(IBEO_gencpp IBEO_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS IBEO_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(IBEO
  "/home/robil/robil2/src/Simulation/IBEO/msg/MultiLaserScan.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/IBEO
)

### Generating Services

### Generating Module File
_generate_module_lisp(IBEO
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/IBEO
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(IBEO_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(IBEO_generate_messages IBEO_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robil/robil2/src/Simulation/IBEO/msg/MultiLaserScan.msg" NAME_WE)
add_dependencies(IBEO_generate_messages_lisp _IBEO_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(IBEO_genlisp)
add_dependencies(IBEO_genlisp IBEO_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS IBEO_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(IBEO
  "/home/robil/robil2/src/Simulation/IBEO/msg/MultiLaserScan.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/IBEO
)

### Generating Services

### Generating Module File
_generate_module_py(IBEO
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/IBEO
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(IBEO_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(IBEO_generate_messages IBEO_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robil/robil2/src/Simulation/IBEO/msg/MultiLaserScan.msg" NAME_WE)
add_dependencies(IBEO_generate_messages_py _IBEO_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(IBEO_genpy)
add_dependencies(IBEO_genpy IBEO_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS IBEO_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/IBEO)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/IBEO
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(IBEO_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/IBEO)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/IBEO
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(IBEO_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/IBEO)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/IBEO\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/IBEO
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(IBEO_generate_messages_py std_msgs_generate_messages_py)
