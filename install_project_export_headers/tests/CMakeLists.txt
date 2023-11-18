add_test(NAME test_shared COMMAND $<TARGET_FILE:hello_world_wDSO2>)

add_test(NAME test_static COMMAND $<TARGET_FILE:hello_world_wAR2>)
