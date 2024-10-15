cmake_minimum_required(VERSION 3.0)

project( ballgame )

find_package( OpenCV REQUIRED )

add_executable( ballgame src/main.cpp )

##add_executable( oke1 src/progrobot.cpp )

target_link_libraries( ballgame ${OpenCV_LIBS} )
