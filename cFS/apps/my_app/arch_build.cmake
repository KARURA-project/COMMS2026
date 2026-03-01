###########################################################
#
# MY_APP platform build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the MY_APP configuration
set(MY_APP_PLATFORM_CONFIG_FILE_LIST
  my_app_internal_cfg.h
  my_app_platform_cfg.h
  my_app_perfids.h
  my_app_msgids.h
)

# Create wrappers around the all the config header files
# This makes them individually overridable by the missions, without modifying
# the distribution default copies
foreach(MY_APP_CFGFILE ${MY_APP_PLATFORM_CONFIG_FILE_LIST})
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
