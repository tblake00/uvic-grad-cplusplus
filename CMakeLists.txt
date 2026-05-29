cmake_minimum_required(VERSION 3.10) 

project(Cipher VERSION 0.10)

# Generate Version.h containing version number
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/include/Version.h.in 
	${CMAKE_CURRENT_SOURCE_DIR}/include/Version.h
) 

# Enable verbose printing during compilation

set(CMAKE_VERBOSE_MAKEFILE ON) 

# Disable compiler specific C++ language extensions 

set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags
# -Wall -Wextra : enable additional warnings
# -Werror       : converts warnings to errors
# -Wshadow      : raise warning if multiple variables have the same name (hiding declarations)
# -pedantic     : raise warning if code violates ISO standards 
# -Wfatal-errors: abort compilation on reaching first error

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

# Include header files from the include directory in compilation

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Specify executable to build

add_executable(cipher 
	${CMAKE_CURRENT_SOURCE_DIR}/cipher.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/TextFormatting.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TransformCharacter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ProcessCommandLine.cpp
)

# Use c++17 standard for language features, PRIVATE specifies that this option applies
# only to 'cipher'

target_compile_features(cipher PRIVATE cxx_std_17)

