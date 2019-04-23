cmake_minimum_required (VERSION 2.8)

file(GLOB_RECURSE srcs
  ${SRC_DIR}/*.cpp
  ${TEST_DIR}/*.cpp
)

file(STRINGS mock.conf strings)
foreach(str IN LISTS strings)
  list(GET str 0 file_)
  list(GET str 1 symbol_)
  message(STATUS ${file_})
  message(STATUS ${symbol_})
  add_custom_command(OUTPUT a.o
	  COMMAND g++ -c ${SRC_DIR}/a/a.cpp -I${SRC_DIR}
      COMMAND objcopy --weaken-symbol=_ZN1A10class_funcEv a.o
      COMMAND objcopy --add-symbol _Z17class_func_origin1A=.text:0x92,weak,function a.o
      COMMAND objcopy --weaken-symbol=_Z11normal_funcv a.o
      COMMAND objcopy --add-symbol _Z18normal_func_originv=.text:0x00,weak,function a.o
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endforeach(str)

list(FILTER srcs EXCLUDE REGEX a.cpp)
list(APPEND srcs ./a.o)

add_executable(MockTest ${srcs})

target_compile_options(MockTest
  PRIVATE
  -I${SRC_DIR}
)

