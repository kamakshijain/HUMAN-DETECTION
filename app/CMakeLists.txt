add_executable(shell-app main.cpp data.cpp detect.cpp train.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries (shell-app ${OpenCV_LIBS})
