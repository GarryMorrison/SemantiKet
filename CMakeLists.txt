# CMakeList.txt : CMake project for SemantiKet, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SemantiKet")

# set verbose cmake:
set(CMAKE_VERBOSE_MAKEFILE ON)

# find build requirements
FIND_PACKAGE(BISON 3.3 REQUIRED)
FIND_PACKAGE(FLEX)

## INCLUDES
# We need this uglyness so <FlexLexer.h> can be found on windows!
INCLUDE_DIRECTORIES(C:/winflexbison/win_flex_bison-2.5.24/)
# include root source directory for includes search
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
# include binary build directory for includes search
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "cmake_current_source_dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "cmake_current_binary_dir: ${CMAKE_CURRENT_BINARY_DIR}")


## SDB CORE
# Parser: generated bison/flex outputs for Parser
BISON_TARGET(Parser src/core/Parser/Parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
FLEX_TARGET(Lexer src/core/Parser/Scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.h)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Parser: set parser header and source files explicitly to avoid any generated bison/flex outputs
set(Parser_SRC "src/core/Parser/Driver.h" "src/core/Parser/Driver.cpp" "src/core/Parser/Scanner.h" "src/core/Parser/Serial.h")

# Core source files:
set(Core_SRC "src/core/misc/misc.h" "src/core/misc/misc.cpp" "src/core/UnitTest/UnitTest.h" "src/core/UnitTest/UnitTest.cpp")

# Add source to this project's executable.
add_executable (SemantiKet "src/SemantiKet.cpp" "src/SemantiKet.h" ${Parser_SRC} ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS} ${Core_SRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SemantiKet PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
