cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE D:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(VCPKG_TARGET_TRIPLET x64-windows-static)

project(wxdemo1)

set(CMAKE_CXX_STANDARD 20)


if(MSVC)
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
else(MSVC)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_STATIC_RUNTIME ON)
endif(MSVC)


# 查找 wxWidgets 库
find_package(wxWidgets CONFIG REQUIRED)

# 设置静态运行时库
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# 设置生成静态链接的可执行文件
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib")

# 添加资源文件
set(RESOURCES
        "D:/dev/vcpkg/packages/wxwidgets_x64-windows-static/include/wx/msw/wx_dpi_aware_pmv2.manifest"
)

add_executable(wxdemo1 WIN32 main.cpp ${RESOURCES}
        MainFrame.cpp
        MainFrame.h
        AlterThread.cpp
        AlterThread.h
        StashThread.h
        StashThread.cpp
        WinTool.cpp
        WinTool.h
        ItemFliter.cpp
        ItemFliter.h
        PoeWork.cpp
        PoeWork.h
        TujinThread.cpp
        TujinThread.h
)

# 链接 wxWidgets 库
target_link_libraries(wxdemo1 PRIVATE wx::core wx::base)

# 包含 wxWidgets 头文件
target_include_directories(wxdemo1 PRIVATE ${wxWidgets_INCLUDE_DIRS})

# 设置资源文件路径
set(CMAKE_RESOURCE_COMPILER_FLAGS "-I${CMAKE_CURRENT_SOURCE_DIR}")
