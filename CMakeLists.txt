cmake_minimum_required(VERSION 3.22)
project(MitkDemo LANGUAGES CXX)
find_program(CCACHE_PROGRAM ccache)
#SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
if(CCACHE_PROGRAM)
  message(STATUS "Set up ccache ...")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Concurrent)
find_package(MITK REQUIRED)
find_package(OpenMP REQUIRED)
find_package(ITK REQUIRED)
find_package(VTK REQUIRED)
file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE UI_FILES "*.ui")
file(GLOB_RECURSE QRC_FILES "*.qrc")

foreach(_source IN ITEMS ${HEADER_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    if(_source_path STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
        set(_group_path "Uncategorized Files")
    else()
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    endif()
    source_group("${_group_path}/Header" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    if(_source_path STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
        set(_group_path "Uncategorized Files")
    else()
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    endif()
    source_group("${_group_path}/Source" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${UI_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    if(_source_path STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
        set(_group_path "Uncategorized Files")
    else()
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    endif()
    source_group("${_group_path}/UI Forms" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${QRC_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    if(_source_path STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
        set(_group_path "Uncategorized Files")
    else()
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    endif()
    source_group("${_group_path}/Resource" FILES "${_source}")
endforeach()

source_group("Generated Files" REGULAR_EXPRESSION "qrc_.*\\.cpp|ui_.*\\.h$|moc.*\\.cpp$|\\.stamp$|\\.rule$")
#include_directories(${CMAKE_SOURCE_DIR}/Base)
#include_directories(${CMAKE_SOURCE_DIR}/Sql)
#include_directories(${CMAKE_SOURCE_DIR}/Login)
#include_directories(${CMAKE_SOURCE_DIR}/Util)
#include_directories(${CMAKE_SOURCE_DIR}/Widgets)
#include_directories(${CMAKE_SOURCE_DIR}/CaseManage)
include_directories(${CMAKE_SOURCE_DIR})
file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(subdir ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
    endif()
endforeach()
usFunctionGenerateModuleInit(SOURCE_FILES)
usFunctionGetResourceSource(TARGET ${PROJECT_NAME} OUT SOURCE_FILES)
set(PROJECT_SOURCES
        ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES} ${QRC_FILES}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS US_MODULE_NAME=${PROJECT_NAME})


#设置输出目录（属性-》常规-》输出目录）（不需要改动）
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin/${CMAKE_GENERATOR_PLATFORM}/$<CONFIGURATION>
    ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib/${CMAKE_GENERATOR_PLATFORM}/$<CONFIGURATION>
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib/${CMAKE_GENERATOR_PLATFORM}/$<CONFIGURATION>
)


target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Concurrent ${ITK_LIBRARIES} ${VTK_LIBRARIES}
MitkCore MitkQtWidgets MitkAlgorithmsExt ${CMAKE_SOURCE_DIR}/lib/vtkDICOM-9.1.lib CppMicroServices
)
target_compile_definitions(${PROJECT_NAME} PRIVATE US_MODULE_NAME=main)
set_property(TARGET ${PROJECT_NAME} PROPERTY US_MODULE_NAME main)

set(InteractionList "")
file(GLOB_RECURSE InteractionFiles "Interactions/*")
foreach(_source IN ITEMS ${InteractionFiles})
    get_filename_component(FILE_NAME ${_source} NAME)
    list(APPEND InteractionList "Interactions/${FILE_NAME}")
endforeach()
usFunctionEmbedResources(TARGET ${PROJECT_NAME} FILES ${InteractionList})
