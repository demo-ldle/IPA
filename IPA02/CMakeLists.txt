cmake_minimum_required(VERSION 2.6)
project(ipa02)

find_package( OpenCV 3.1 REQUIRED )

include_directories( 
    ${OpenCV_INCLUDE_DIRS} 
)
add_executable(ipa main.cpp)

add_library( conv conv.cpp )

target_link_libraries(ipa ${OpenCV_LIBS} conv)

install(TARGETS ipa RUNTIME DESTINATION bin)