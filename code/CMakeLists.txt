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
    tracking/atg_reference_mainline.cpp
    ../atg_reference/port/reference_globals.c
    ../atg_reference/port/reference_step.c
    ../atg_reference/Project/CODE/shy_Image.c
    ../atg_reference/Project/CODE/imgproc.c
    ../atg_reference/Project/CODE/utils.c
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
    ../atg_reference/port
    ../atg_reference/Project/CODE
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

    add_host_plain_test(config_parsing_test
        test/config_parsing_test.cpp
        core/config.cpp
    )

    add_host_plain_test(options_parsing_test
        test/options_parsing_test.cpp
        app/options.cpp
    )
endif()
