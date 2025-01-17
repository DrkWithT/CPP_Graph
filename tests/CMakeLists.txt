add_executable(test_ds)
target_include_directories(test_ds PUBLIC "${CPPG_INCLUDES}")
target_sources(test_ds PRIVATE test_ds.cpp)
add_test(NAME test_ds COMMAND "$<TARGET_FILE:test_ds>")

# add_executable(test_algos)
# target_include_directories(test_algos PUBLIC "${CPPG_INCLUDES}")
# target_sources(test_algos PRIVATE test_algos.cpp)
# add_test(NAME test_algos COMMAND "$<TARGET_FILE:test_algos>")
