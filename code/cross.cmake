# SMARTCAR_CROSS_COMPILE=ON 表示交叉编译，OFF 表示使用当前主机编译器。
option(SMARTCAR_CROSS_COMPILE "Build for LS2K0300 LoongArch target" ON)

if(SMARTCAR_CROSS_COMPILE)
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR loongson)
    set(TOOLCHAIN_DIR "/opt/ls_2k0300_env/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.6")
    set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/bin/loongarch64-linux-gnu-g++")
    set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/bin/loongarch64-linux-gnu-gcc")

    set(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_DIR}")
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()
