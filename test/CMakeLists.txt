cmake_minimum_required (VERSION 2.8)

file(GLOB_RECURSE srcs
  ${SRC_DIR}/*.cpp
  ${TEST_DIR}/*.cpp
)

set(target_files "")
set(target_files_obj "")

file(STRINGS mock.conf strings)
foreach(str IN LISTS strings)
  list(GET str 0 file)
  list(GET str 1 symbols_)
  list(GET str 2 symbols_origin_)
  list(GET str 3 symbols_offset_)

  # add to target_files
  list(APPEND target_files ${file})

  # extract obj name and add to target_files_obj
  string(REPLACE ".cpp" ".o" file_obj ${file})
  string(REGEX REPLACE ".*/" "" file_obj ${file_obj})
  list(APPEND target_files_obj ${file_obj})

  # compile obj
  execute_process(
    COMMAND g++ -c ${PROJECT_SOURCE_DIR}/${file} -I${SRC_DIR} -o ${file_obj}
  )

  # change string to list
  string(REPLACE "," ";" symbols ${symbols_})
  string(REPLACE "," ";" symbols_origin ${symbols_origin_})
  string(REPLACE "," ";" symbols_offset ${symbols_offset_})

  # cal length and begin to loop
  list(LENGTH symbols symbols_num)
  MATH(EXPR symbols_num "${symbols_num}-1")
  foreach(i RANGE  ${symbols_num})
	list(GET symbols ${i} symbol)
	list(GET symbols_origin ${i} symbol_origin)
	list(GET symbols_offset ${i} symbol_offset)
	message(STATUS ${symbol})
	message(STATUS ${symbol_origin})
	message(STATUS ${symbol_offset})
	execute_process(
	  # weak origin symbol
      COMMAND objcopy --weaken-symbol=${symbol} ${file_obj}
	  # add new symbol, name is xxx_origin
      COMMAND objcopy --add-symbol ${symbol_origin}=.text:${symbol_offset},weak,function ${file_obj}
	)
  endforeach(i)
endforeach(str)

# del target_files in srcs and add obj files in srcs
list(LENGTH target_files target_num)
MATH(EXPR target_num "${target_num}-1")
foreach(j RANGE ${target_num})
  list(GET target_files ${j} target_file) 
  list(GET target_files_obj ${j} target_file_obj) 
  list(FILTER srcs EXCLUDE REGEX ${target_file})
  list(APPEND srcs ${PROJECT_BINARY_DIR}/${target_file_obj})
endforeach(j)
message(STATUS ${srcs})

add_executable(MockTest ${srcs})

target_compile_options(MockTest
  PRIVATE
  -I${SRC_DIR}
)

