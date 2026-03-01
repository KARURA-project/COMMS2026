###########################################################
#
# MY_APP mission build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the MY_APP configuration
set(MY_APP_MISSION_CONFIG_FILE_LIST
  my_app_fcncodes.h
  my_app_interface_cfg.h
  my_app_mission_cfg.h
  my_app_perfids.h
  my_app_msg.h
  my_app_msgdefs.h
  my_app_msgstruct.h
  my_app_tbl.h
  my_app_tbldefs.h
  my_app_tblstruct.h
  my_app_topicids.h
)

if (CFE_EDS_ENABLED_BUILD)

  # In an EDS-based build, these files come generated from the EDS tool
  set(MY_APP_CFGFILE_SRC_my_app_interface_cfg "my_app_eds_designparameters.h")
  set(MY_APP_CFGFILE_SRC_my_app_tbldefs       "my_app_eds_typedefs.h")
  set(MY_APP_CFGFILE_SRC_my_app_tblstruct     "my_app_eds_typedefs.h")
  set(MY_APP_CFGFILE_SRC_my_app_msgdefs       "my_app_eds_typedefs.h")
  set(MY_APP_CFGFILE_SRC_my_app_msgstruct     "my_app_eds_typedefs.h")
  set(MY_APP_CFGFILE_SRC_my_app_fcncodes      "my_app_eds_cc.h")

endif(CFE_EDS_ENABLED_BUILD)

# Create wrappers around the all the config header files
# This makes them individually overridable by the missions, without modifying
# the distribution default copies
foreach(MY_APP_CFGFILE ${MY_APP_MISSION_CONFIG_FILE_LIST})
  get_filename_component(CFGKEY "${MY_APP_CFGFILE}" NAME_WE)
  if (DEFINED MY_APP_CFGFILE_SRC_${CFGKEY})
    set(DEFAULT_SOURCE GENERATED_FILE "${MY_APP_CFGFILE_SRC_${CFGKEY}}")
  else()
    set(DEFAULT_SOURCE FALLBACK_FILE "${CMAKE_CURRENT_LIST_DIR}/config/default_${MY_APP_CFGFILE}")
  endif()
  generate_config_includefile(
    FILE_NAME           "${MY_APP_CFGFILE}"
    ${DEFAULT_SOURCE}
  )
endforeach()
