cmake_minimum_required(VERSION 3.20)
project(WinDarkModeTest LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WinDarkModeTest WIN32
    main.cpp
    dialog.rc
)

target_include_directories(WinDarkModeTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_definitions(WinDarkModeTest PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
)

target_link_libraries(WinDarkModeTest PRIVATE
    uxtheme
    dwmapi
    comctl32
    comdlg32
)
