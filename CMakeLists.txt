cmake_minimum_required(VERSION 3.20)                            # minimum cmake version required
project(entropy_overlap VERSION 1.0)                            # project name + skip C compiler check

add_executable(entropy_overlap main.cpp)                        # builds an exe named "entropy_overlap" from main.cpp
target_include_directories(entropy_overlap PRIVATE include)
set_target_properties(entropy_overlap PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)