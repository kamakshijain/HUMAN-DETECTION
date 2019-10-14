set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    testdata.cpp
    ../app/data.cpp
    testtrain.cpp
    ../app/train.cpp
    testdetect.cpp
    ../app/detect.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS})
find_package(OPenCV REQUIRED PATHS " /home/sayan/opencv/build")
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS})

