cmake_minimum_required (VERSION 3.2)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUERED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

set (PROJECT lifestream_test)

project (${PROJECT})

set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories (
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/source
                    )

set (SOURCES
        ${SOURCE_DIR}/Application.cpp
        ${SOURCE_DIR}/AttributeHandlers.cpp
        ${SOURCE_DIR}/InputTranslator.cpp
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/MessageHandlers.cpp
        ${SOURCE_DIR}/MessageQueue.cpp
        ${SOURCE_DIR}/MessageQueueHandler.cpp
        ${SOURCE_DIR}/PrimeFactorSearch.cpp
        ${SOURCE_DIR}/TaskQueque.cpp
        ${SOURCE_DIR}/ThreadPool.cpp
        ${SOURCE_DIR}/WorkloadManager.cpp
    )

add_executable(
    ${PROJECT}
    ${SOURCES}
)

install(
    TARGETS
    ${PROJECT}
    RUNTIME
    DESTINATION
    ${EXECUTABLE_OUTPUT_PATH}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_NANOSLEEP")

if(${CMAKE_SYSTEM} MATCHES "Darwin")
    include(
        macosx.cmake
    )
else()
    include(
        common.cmake
    )
endif()
