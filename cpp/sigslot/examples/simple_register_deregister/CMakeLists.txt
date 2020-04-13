project(SigSlot-Tests-Simple-Connection-Tests)

set(CMAKE_CXX_STANDARD 17)
include_directories("../../src")

add_executable(simple_conn_disconn test.cpp)

