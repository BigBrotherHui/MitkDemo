cmake_minimum_required(VERSION 3.18)
project(DentalRobot LANGUAGES CXX)
find_program(CCACHE_PROGRAM ccache)
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



include_directories("../lib/RCF-3.2.413/include")
link_directories("../lib/RCF-3.2.413/lib")
include_directories("../lib/log4cplus/include")
link_directories("../lib/log4cplus/lib")

link_directories("../lib")

find_package(CUDA)
# nvcc flags
set(CUDA_NVCC_FLAGS -gencode arch=compute_20,code=sm_20;-G;-g)
include_directories("${CUDA_INCLUDE_DIRS}")
find_package(Qt5 REQUIRED COMPONENTS Widgets Concurrent)
find_package(MITK REQUIRED)
find_package(OpenMP REQUIRED)
find_package(ITK REQUIRED)
find_package(VTK REQUIRED)
find_package(Eigen3 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE UI_FILES "*.ui")
file(GLOB_RECURSE QRC_FILES "*.qrc")

set(PROJECT_SOURCES
        ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES} ${QRC_FILES}
)

# 添加源文件
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

# 将源文件按目录分组
foreach(_source IN ITEMS ${SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()


source_group("Header Files" REGULAR_EXPRESSION ".h$")
source_group("Source Files" FILES ${SRC_FILES})
source_group("Forms" REGULAR_EXPRESSION ".ui$")
source_group("Generated Files" REGULAR_EXPRESSION "ui_.*\\.h$|moc.*\\.cpp$|\\.stamp$|\\.rule$")
include_directories(${CMAKE_SOURCE_DIR}/Base)
include_directories(${CMAKE_SOURCE_DIR}/Sql)
include_directories(${CMAKE_SOURCE_DIR}/Login)
include_directories(${CMAKE_SOURCE_DIR}/Util)
include_directories(${CMAKE_SOURCE_DIR}/Widgets)
include_directories(${CMAKE_SOURCE_DIR}/CaseManage)
include_directories(${CMAKE_SOURCE_DIR}/Robot)
include_directories(${CMAKE_SOURCE_DIR}/Navigation)
include_directories(${CMAKE_SOURCE_DIR}/PreOperationDesign)
include_directories(${CMAKE_SOURCE_DIR}/Rehearsal)
include_directories(${CMAKE_SOURCE_DIR}/SystemControl)
include_directories(${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} qr.qrc)


target_compile_definitions(DentalRobot PUBLIC "_WIN32_WINNT=0x0501")
target_compile_definitions(DentalRobot PUBLIC "POCO_NO_UNWINDOWS")
target_compile_definitions(DentalRobot PUBLIC "WIN32_LEAN_AND_MEAN")
target_compile_definitions(DentalRobot PUBLIC "NOMINMAX")

#设置输出目录（属性-》常规-》输出目录）（不需要改动）
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin/${CMAKE_GENERATOR_PLATFORM}/$<CONFIGURATION>
    ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib/${CMAKE_GENERATOR_PLATFORM}/$<CONFIGURATION>
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib/${CMAKE_GENERATOR_PLATFORM}/$<CONFIGURATION>
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Concurrent ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${CUDA_LIBRARIES}
MitkCore MitkQtWidgets MitkMapperExt MitkDICOM MitkAlgorithmsExt vtkDICOM-9.1.lib RcfLib_r.lib log4cplus.lib Eigen3::Eigen


)

vtk_module_autoinit(TARGETS DentalRobot MODULES ${VTK_LIBRARIES})
