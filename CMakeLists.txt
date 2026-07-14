cmake_minimum_required(VERSION 3.20)                            # minimum cmake version required
project(entropy-collision VERSION 1.0)                          # project name + skip C compiler check

add_executable(entropy-collision main.cpp)                      # builds an exe named "entropy-collision" from main.cpp
target_include_directories(entropy-collision PRIVATE include)
set_target_properties(entropy-collision PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)