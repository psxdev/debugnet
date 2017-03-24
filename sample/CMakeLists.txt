cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif()
endif()

project(debugnetsample)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_TITLEID "BIGB00001")

set(CFLAGS "-Wl,-q -Wall -O3")

add_executable(${PROJECT_NAME}.elf main.c)
target_compile_options(${PROJECT_NAME}.elf PRIVATE ${CFLAGS})

target_link_libraries(${PROJECT_NAME}.elf
        c
	debugnet
	SceNetCtl_stub
	SceNet_stub
	SceSysmodule_stub
	)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME}.elf)
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
	NAME ${PROJECT_NAME}
        )
