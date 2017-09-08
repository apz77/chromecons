set(BOOST_LIB_DIR ../../libs/boost)

add_subdirectory(sqlite)
add_subdirectory(http-parser)

message("${CMAKE_CURRENT_LIST_DIR}")

if (WIN32)
    message(STATUS "Bootstrapping boost (Windows)")

    execute_process(COMMAND bootstrap.bat
                  WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/boost"
                  RESULT_VARIABLE boostrap_result)

    if (bootstrap_result) 
	message(FATAL_ERROR "boost: Boost bootstrap failed")
    endif()

    execute_process(COMMAND b2 install
			"link=static"
			"address-model=32"
			"--prefix=${BOOST_LIB_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/boost"
		  RESULT_VARIABLE bootstrap_result)

else()
    message(STATUS "Bootstrapping boost (Linux)")
    execute_process(COMMAND "./bootstrap.sh"
			"--prefix=${BOOST_LIB_DIR}"
			WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/boost"
			RESULT_VARIABLE bootstrap_result)

    if (bootstrap_result) 
	message(FATAL_ERROR "boost: Boost bootstrap failed ${bootstrap_result}")
    endif()

    execute_process(COMMAND ./b2 install
			"link=static"
			"address-model=32"
			WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/boost"
			RESULT_VARIABLE bootstrap_result)
endif()

if (bootstrap_result) 
    message(FATAL_ERROR "boost: Boost build failed ${bootstrap_result}")
endif()
