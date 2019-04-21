cmake_minimum_required (VERSION 2.8)

project (MockTest)

set(MOCK_SRCS "")

file(STRINGS mock.conf strings)
foreach(str IN LISTS strings)
  list(GET str 0 file_)
  list(GET str 1 symbol_)
  message(STATUS ${file_})
  message(STATUS ${symbol_})
  add_custom_command(OUTPUT target.o
      COMMAND g++ -c ../target.cpp
      COMMAND objcopy --weaken-symbol=_ZN1A10class_funcEv target.o
      COMMAND objcopy --add-symbol _Z17class_func_origin1A=.text:0x92,weak,function target.o
      COMMAND objcopy --weaken-symbol=_Z11normal_funcv target.o
      COMMAND objcopy --add-symbol _Z18normal_func_originv=.text:0x00,weak,function target.o
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endforeach(str)

set(DIR_SRCS 
    ./test_case.cpp
    ./target.o)

#aux_source_directory(. DIR_SRCS)
add_executable(MockTest ${DIR_SRCS})

