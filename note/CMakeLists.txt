cmake_minimum_required(VERSION 2.8)

add_definitions("-std=c++11")

link_libraries(
    sqlite3
)

add_executable(mynote main.cc handler.cc)
add_executable(note note.cc)
