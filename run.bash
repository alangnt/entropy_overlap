#!/bin/bash
if [[ "$1" == "root" ]]; then
  rm -rf build
  mkdir build && cd build

  cmake ..
  cmake --build .
else
  cd build
fi

./entropy_overlap