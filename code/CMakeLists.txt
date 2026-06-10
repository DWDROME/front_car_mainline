cmake_minimum_required(VERSION 3.5.0)

set(PROJ_NAME front_car_mainline)
project(${PROJ_NAME} VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(cross.cmake)

if(SMARTCAR_CROSS_COMPILE)
    set(COMMON_FLAGS "-O3 -march=loongarch64 -mtune=loongarch64 -fPIC -ffunction-sections -fdata-sections -Wall")
    set(CMAKE_PREFIX_PATH "/opt/ls_2k0300_env/opencv_4_10_build")
else()
    set(COMMON_FLAGS "-O2 -fPIC -ffunction-sections -fdata-sections -Wall")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV_INCLUDE: ${OpenCV_INCLUDE_DIRS}, OpenCV_LIBS: ${OpenCV_LIBS}")

aux_source_directory(../../../libraries/zf_common ZF_COMMON_SRCS)
aux_source_directory(../../../libraries/zf_device ZF_DEVICE_SRCS)
aux_source_directory(../../../libraries/zf_driver ZF_DRIVER_SRCS)
aux_source_directory(../../../libraries/zf_components/seekfree_assistant ZF_ASSISTANT_SRCS)

set(DIR_SRCS
    app/main.cpp
    app/assistant.cpp
    app/options.cpp
    app/report.cpp
    app/runners.cpp
    drivers/device.cpp
    drivers/drive_output.cpp
    drivers/imu_feedback.cpp
    tracking/perspective.cpp
    tracking/ipm_table_generated.cpp
    tracking/autop_reference_ipm_bridge.cpp
    tracking/autop_reference_mainline.cpp
    ../autop_reference/port/reference_globals.c
    ../autop_reference/port/reference_step.c
    ../autop_reference/Project/CODE/imgproc.c
    ../autop_reference/Project/CODE/utils.c
    ../autop_reference/Project/CODE/cross.c
    ../autop_reference/Project/CODE/circle.c
    ../autop_reference/Project/CODE/flash_param.c
    core/control.cpp
    core/config.cpp
    ${ZF_ASSISTANT_SRCS}
    ${ZF_COMMON_SRCS}
    ${ZF_DEVICE_SRCS}
    ${ZF_DRIVER_SRCS}
)

add_executable(${PROJ_NAME} ${DIR_SRCS})
target_include_directories(${PROJ_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    .
    ..
    ../utils
    app
    drivers
    tracking
    core
    ../autop_reference/port
    ../autop_reference/Project/CODE
    ../autop_reference/Project/USER/inc
    telemetry
    upper_monitor
    utils
    test
    scripts
    tools
    ../../../libraries/zf_components/seekfree_assistant
    ../../../libraries/zf_common
    ../../../libraries/zf_device
    ../../../libraries/zf_driver
)
set_target_properties(${PROJ_NAME} PROPERTIES
    INSTALL_RPATH "/opt/ls_2k0300_env/opencv_4_10_build/lib"
    BUILD_WITH_INSTALL_RPATH ON
)

target_link_libraries(
    ${PROJ_NAME}
    ${OpenCV_LIBS}
    pthread
    m
)

add_executable(key_supervisor
    tools/key_supervisor.cpp
    ${ZF_COMMON_SRCS}
    ${ZF_DRIVER_SRCS}
)
target_include_directories(key_supervisor PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ../../../libraries/zf_common
    ../../../libraries/zf_driver
)
set_target_properties(key_supervisor PROPERTIES
    INSTALL_RPATH "/opt/ls_2k0300_env/opencv_4_10_build/lib"
    BUILD_WITH_INSTALL_RPATH ON
)
target_link_libraries(
    key_supervisor
    ${OpenCV_LIBS}
    pthread
    m
)

if(NOT SMARTCAR_CROSS_COMPILE)
    function(add_host_tracking_test TARGET_NAME)
        add_executable(${TARGET_NAME} ${ARGN})
        target_include_directories(${TARGET_NAME} PRIVATE
            ${OpenCV_INCLUDE_DIRS}
            .
            ..
            tracking
        )
        target_link_libraries(
            ${TARGET_NAME}
            ${OpenCV_LIBS}
            m
        )
    endfunction()

    function(add_host_plain_test TARGET_NAME)
        add_executable(${TARGET_NAME} ${ARGN})
        target_include_directories(${TARGET_NAME} PRIVATE
            .
            ..
            app
            core
        )
        target_link_libraries(
            ${TARGET_NAME}
            m
        )
    endfunction()

    add_host_tracking_test(cross_farline_reuse_test
        test/cross_farline_reuse_test.cpp
        tracking/imgproc.cpp
        tracking/perspective.cpp
        tracking/ipm_table_generated.cpp
    )

    add_host_tracking_test(midline_lookahead_test
        test/midline_lookahead_test.cpp
        tracking/perspective.cpp
        tracking/ipm_table_generated.cpp
    )

    add_host_tracking_test(line_trace_contract_test
        test/line_trace_contract_test.cpp
        tracking/imgproc.cpp
        tracking/perspective.cpp
        tracking/ipm_table_generated.cpp
    )

    add_host_tracking_test(boundary_contract_test
        test/boundary_contract_test.cpp
        tracking/imgproc.cpp
        tracking/perspective.cpp
        tracking/ipm_table_generated.cpp
        tracking/boundary.cpp
    )

    add_host_tracking_test(element_entry_contract_test
        test/element_entry_contract_test.cpp
        tracking/imgproc.cpp
        tracking/perspective.cpp
        tracking/ipm_table_generated.cpp
        tracking/boundary.cpp
        tracking/cross.cpp
        tracking/ring.cpp
    )

    add_host_tracking_test(search_center_learning_test
        test/search_center_learning_test.cpp
        tracking/imgproc.cpp
        tracking/perspective.cpp
        tracking/ipm_table_generated.cpp
        tracking/boundary.cpp
        tracking/zebra.cpp
        tracking/ring.cpp
        tracking/element.cpp
        tracking/cross.cpp
    )

    add_host_tracking_test(ring_opp_diag_test
        test/ring_opp_diag_test.cpp
        tracking/imgproc.cpp
        tracking/perspective.cpp
        tracking/ipm_table_generated.cpp
        tracking/boundary.cpp
    )

    add_host_plain_test(config_parsing_test
        test/config_parsing_test.cpp
        core/config.cpp
    )

    add_host_plain_test(options_parsing_test
        test/options_parsing_test.cpp
        app/options.cpp
    )
endif()
