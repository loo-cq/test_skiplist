# cmake_minimum_required(VERSION 2.8)
# project(test)
# include_directories(./include)
# set(SRC_LIST  ./src/main.cpp)
# add_executable(main ${SRC_LIST})

cmake_minimum_required(VERSION 3.5)
project(Red_Black_Tree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp skiplist.h avl_tree.h)
add_executable(Red_Black_Tree ${SOURCE_FILES})


# cmake_minimum_required(VERSION 3.5)
# project(Red_Black_Tree)

# set(CMAKE_CXX_STANDARD 11)

# set(SOURCE_FILES  avl_tree_test.cpp avl_tree.h)
# add_executable(Red_Black_Tree ${SOURCE_FILES})