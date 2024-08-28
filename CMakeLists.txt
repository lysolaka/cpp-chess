cmake_minimum_required(VERSION 3.28)

project(cpp-chess
  LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

include(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX(cwchar HAVE_WCHAR)

if (HAVE_WCHAR)
else()
  cmake_language(EXIT 1)
endif()

CHECK_INCLUDE_FILE_CXX(vector HAVE_VECTOR)
CHECK_INCLUDE_FILE_CXX(initializer_list HAVE_INIT_LIST)
CHECK_INCLUDE_FILE_CXX(stdexcept HAVE_EXCEPT)
CHECK_INCLUDE_FILE_CXX(clocale HAVE_LOCALE)

option(USE_COLOR "Enable colour output" ON)

add_library(cpp-chess-core STATIC
  src/core/piece.cpp
  src/core/board.cpp
)
target_include_directories(cpp-chess-core PUBLIC src/core/)
target_compile_features(cpp-chess-core PUBLIC cxx_std_23)
target_compile_definitions(cpp-chess-core PRIVATE
  "$<$<CONFIG:Debug>:CPP_CHESS_DEBUG>")

add_library(cpp-chess-ui STATIC
  src/ui/display.cpp
  src/ui/control.cpp
)
target_include_directories(cpp-chess-ui PUBLIC src/ui/)
target_compile_features(cpp-chess-ui PUBLIC cxx_std_23)
target_compile_definitions(cpp-chess-ui PRIVATE
  "$<$<CONFIG:Debug>:CPP_CHESS_DEBUG>"
  "$<$<BOOL:USE_COLOR>:CPP_CHESS_COLOR>"
)


add_executable(cpp-chess src/main.cpp)
target_link_libraries(cpp-chess PUBLIC
  cpp-chess-core
  cpp-chess-ui
)
