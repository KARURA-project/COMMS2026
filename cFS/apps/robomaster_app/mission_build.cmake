###########################################################
#
# ROBOMASTER_APP mission build setup
#
###########################################################

# The list of header files that control the ROBOMASTER_APP configuration
set(ROBOMASTER_APP_MISSION_CONFIG_FILE_LIST
  robomaster_app_fcncodes.h
  robomaster_app_interface_cfg.h
  robomaster_app_mission_cfg.h
  robomaster_app_perfids.h
  robomaster_app_msg.h
  robomaster_app_msgdefs.h
  robomaster_app_msgstruct.h
  robomaster_app_tbl.h
  robomaster_app_tbldefs.h
  robomaster_app_tblstruct.h
  robomaster_app_topicids.h
)

# Create wrappers around the all the config header files
foreach(ROBOMASTER_APP_CFGFILE ${ROBOMASTER_APP_MISSION_CONFIG_FILE_LIST})
  get_filename_component(CFGKEY "${ROBOMASTER_APP_CFGFILE}" NAME_WE)
  if (DEFINED ROBOMASTER_APP_CFGFILE_SRC_${CFGKEY})
    set(DEFAULT_SOURCE GENERATED_FILE "${ROBOMASTER_APP_CFGFILE_SRC_${CFGKEY}}")
  else()
    set(DEFAULT_SOURCE FALLBACK_FILE "${CMAKE_CURRENT_LIST_DIR}/config/default_${ROBOMASTER_APP_CFGFILE}")
  endif()
  generate_config_includefile(
    FILE_NAME           "${ROBOMASTER_APP_CFGFILE}"
    ${DEFAULT_SOURCE}
  )
endforeach()
