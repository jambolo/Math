cmake_minimum_required (VERSION 3.10)
project(MyMath CXX)

option(BUILD_SHARED_LIBS "Build libraries as DLLs" FALSE)
set(${PROJECT_NAME}_DOXYGEN_OUTPUT_DIRECTORY "" CACHE PATH "Doxygen output directory (empty to disable)")

if(${PROJECT_NAME}_DOXYGEN_OUTPUT_DIRECTORY)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_OUTPUT_DIRECTORY ${${PROJECT_NAME}_DOXYGEN_OUTPUT_DIRECTORY})
        configure_file(Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)
        add_custom_target(doxygen ALL ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
            SOURCES ${PROJECT_BINARY_DIR}/Doxyfile
    )
    endif(DOXYGEN_FOUND)
endif()

#set(${PROJECT_NAME}_VERSION_MAJOR 0)
#set(${PROJECT_NAME}_VERSION_MINOR 1)
#configure_file("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_BINARY_DIR}/Version.h")

set(PUBLIC_INCLUDE_PATHS
    include
)

set(PRIVATE_INCLUDE_PATHS
    .
    include/MyMath
)

set(SOURCES
    include/MyMath/Box.h
    include/MyMath/Cone.h
    include/MyMath/Constants.h
    include/MyMath/Determinant.h
    include/MyMath/FastMath.h
    include/MyMath/FixedPoint.h
    include/MyMath/Frustum.h
    include/MyMath/Intersectable.h
    include/MyMath/Line.h
    include/MyMath/MyMath.h
    include/MyMath/Matrix22.h
    include/MyMath/Matrix22d.h
    include/MyMath/Matrix33.h
    include/MyMath/Matrix33d.h
    include/MyMath/Matrix43.h
    include/MyMath/Matrix43d.h
    include/MyMath/Matrix44.h
    include/MyMath/Matrix44d.h
    include/MyMath/Plane.h
    include/MyMath/Point.h
    include/MyMath/Probability.h
    include/MyMath/Quaternion.h
    include/MyMath/Range.h
    include/MyMath/Sphere.h
    include/MyMath/Vector2.h
    include/MyMath/Vector2d.h
    include/MyMath/Vector2i.h
    include/MyMath/Vector3.h
    include/MyMath/Vector3d.h
    include/MyMath/Vector3i.h
    include/MyMath/Vector4.h
    include/MyMath/Vector4d.h
    
    Box.cpp
    FixedPoint.cpp
    Frustum.cpp
    Intersectable.cpp
    Line.cpp
    MyMath.cpp
    Matrix22.cpp
    Matrix22d.cpp
    Matrix33.cpp
    Matrix33d.cpp
    Matrix43.cpp
    Matrix43d.cpp
    Matrix44.cpp
    Matrix44d.cpp
    Plane.cpp
    Probability.cpp
    Quaternion.cpp
    Vector2.cpp
    Vector2d.cpp
    Vector2i.cpp
    Vector3.cpp
    Vector3d.cpp
    Vector3i.cpp
    Vector4.cpp
    Vector4d.cpp
)
source_group(Sources FILE ${SOURCES})

add_library(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        -DNOMINMAX
        -DWIN32_LEAN_AND_MEAN
        -DVC_EXTRALEAN
        -D_CRT_SECURE_NO_WARNINGS
        -D_SECURE_SCL=0
        -D_SCL_SECURE_NO_WARNINGS
)
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE_PATHS} PRIVATE ${PRIVATE_INCLUDE_PATHS})
target_link_libraries(${PROJECT_NAME} Misc)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    message(STATUS "Testing is enabled. Turn on BUILD_TESTING to build tests.")
    if(BUILD_TESTING)
        add_subdirectory(test)
    endif()
endif()