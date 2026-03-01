project(CFE_MY_APP C)

set(APP_SRC_FILES
  fsw/src/my_app.c
  fsw/src/my_app_cmds.c
  fsw/src/my_app_utils.c
)

if (CFE_EDS_ENABLED_BUILD)
  list(APPEND APP_SRC_FILES
    fsw/src/my_app_eds_dispatch.c
  )
else()
  list(APPEND APP_SRC_FILES
    fsw/src/my_app_dispatch.c
  )
endif()

# Create the app module
add_cfe_app(my_app ${APP_SRC_FILES})

target_include_directories(my_app PUBLIC fsw/inc)
# to call library-provided functions

# Add table
add_cfe_tables(my_app fsw/tables/my_app_tbl.c)

# If UT is enabled, then add the tests from the subdirectory
# Note that this is an app, and therefore does not provide
# stub functions, as other entities would not typically make
# direct function calls into this application.
if (ENABLE_UNIT_TESTS)
  add_subdirectory(unit-test)
endif (ENABLE_UNIT_TESTS)
