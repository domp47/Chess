cmake_minimum_required(VERSION 2.8.12)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/..)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core  REQUIRED)
find_package(Qt5Gui  REQUIRED)
find_package(Qt5Widgets  REQUIRED)

include_directories(../Include)

set( project_sources
        ./main.cpp
        ./GUI/window.cpp
        ./GUI/colors.cpp
        ./GUI/imageMap.cpp
        ./Board/board.cpp
        ./Board/Moves/pawn.cpp
        ./Board/Moves/rook.cpp
        ./Board/Moves/knight.cpp
        ./Board/Moves/bishop.cpp
        ./Board/Moves/queen.cpp
        ./Board/Moves/king.cpp
        ./Board/elPassant.cpp
        ./AI/alphaBeta.cpp
        ./AI/evalMap.cpp
        ./AI/nn.cpp
        ./Controller/controller.cpp
        ./Controller/chess.cpp
        ./Controller/move.cpp
        )

set(headers
        ./GUI/window.h
        ./GUI/colors.h
        ./GUI/imageMap.h
        ./Board/board.h
        ./Board/Moves/pawn.h
        ./Board/Moves/rook.h
        ./Board/Moves/knight.h
        ./Board/Moves/bishop.h
        ./Board/Moves/queen.h
        ./Board/Moves/king.h
        ./Board/elPassant.h
        ./AI/alphaBeta.h
        ./AI/evalMap.h
        ./AI/nn.h
        ./Controller/controller.h
        ./Controller/chess.h
        ./Controller/move.h
        )

add_executable(chess
  ${project_sources}
)

link_directories(/lib/x86_64-linux-gnu/)

target_link_libraries(chess -lpthread ${CMAKE_CURRENT_SOURCE_DIR}/../Lib/libtensorflow_cc.so ${CMAKE_CURRENT_SOURCE_DIR}/../Lib/libtensorflow_framework.so)

qt5_use_modules( chess Core )
qt5_use_modules( chess Gui )
qt5_use_modules( chess Widgets)