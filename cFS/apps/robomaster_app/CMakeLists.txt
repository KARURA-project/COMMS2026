project(ROBOMASTER_APP C)

set(APP_SRC_FILES
  fsw/src/robomaster_app.c
  fsw/src/robomaster_driver.c
)

# Create the app module
add_cfe_app(robomaster_app ${APP_SRC_FILES})

target_include_directories(robomaster_app PUBLIC fsw/inc)

# If UT is enabled, then add the tests from the subdirectory
if (ENABLE_UNIT_TESTS)
  add_subdirectory(unit-test)
endif(ENABLE_UNIT_TESTS)
