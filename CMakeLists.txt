# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# название проекта
project(Algorithms-and-Data-Structures)

# затем следует список инструкций для подключения проектов из подкаталогов

include(cmake/function.cmake)         # подхватываем функции, реализованные в файле function.cmake
                                      # для простоты мы объединили наборы команд для создания статической библиотеки
								      # и для создания исполняемого проекта в отдельные функции
   # подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_easy_example
add_subdirectory(lib_monom)
add_subdirectory(lib_polynom)
add_subdirectory(lib_list)
add_subdirectory(lib_skiplist)
add_subdirectory(lib_stack)
add_subdirectory(lib_queue)
add_subdirectory(lib_lexem)
add_subdirectory(lib_expression)
add_subdirectory(lib_parser)
add_subdirectory(lib_itable)
add_subdirectory(lib_tablebase)
add_subdirectory(lib_TVector)
add_subdirectory(lib_sortedtable)
add_subdirectory(lib_sortedtableavltree)
add_subdirectory(lib_sortedtablebinarytree)
add_subdirectory(lib_unsortedtable)
add_subdirectory(lib_unsortedtabletree)
add_subdirectory(lib_unsortedtablelist)
add_subdirectory(lib_basictree)
add_subdirectory(lib_avltree)
add_subdirectory(lib_hashtablechain)
add_subdirectory(lib_basehash)
add_subdirectory(lib_sortedtableRB)
add_subdirectory(lib_RBtree)
add_subdirectory(lib_hashtableaddress)
add_subdirectory(lib_binarysearchtree)
add_subdirectory(lib_doubly_linked_list)
add_subdirectory(main)                # подключаем дополнительный CMakeLists.txt из подкаталога с именем main

option(BTEST "build test?" ON)        # указываем подключаем ли google-тесты (ON или YES) или нет (OFF или NO)

if(BTEST)                             # если тесты подключены         
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()


