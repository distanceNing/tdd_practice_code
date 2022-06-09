# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/share/tdd_app/cmake-build-debug/_deps/googletest-src"
  "D:/share/tdd_app/cmake-build-debug/_deps/googletest-build"
  "D:/share/tdd_app/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "D:/share/tdd_app/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "D:/share/tdd_app/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "D:/share/tdd_app/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "D:/share/tdd_app/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/share/tdd_app/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
