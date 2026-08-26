cmake_minimum_required(VERSION 3.20)
project(dual_cursor_win32 LANGUAGES CXX)

add_executable(dual_cursor_win32 WIN32 src/main.cpp)
target_compile_features(dual_cursor_win32 PRIVATE cxx_std_17)
target_compile_definitions(dual_cursor_win32 PRIVATE UNICODE _UNICODE WIN32_LEAN_AND_MEAN NOMINMAX)
target_link_libraries(dual_cursor_win32 PRIVATE user32 gdi32)
