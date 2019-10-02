cmake_minimum_required(VERSION 2.6)
project(ipa02)

find_package( OpenCV 3.1 REQUIRED )

include_directories( 
    ${OpenCV_INCLUDE_DIRS} 
)


add_library( conv conv.cpp )

add_executable(ipa01 ipa01_main.cpp)
target_link_libraries(ipa01 ${OpenCV_LIBS} conv)

add_executable(ipa02 ipa02_main.cpp)
target_link_libraries(ipa02 ${OpenCV_LIBS} conv)

add_executable(ipa03 ipa03_main.cpp)
target_link_libraries(ipa03 ${OpenCV_LIBS} conv)
#install(TARGETS ipa01 RUNTIME DESTINATION bin)