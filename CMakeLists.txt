cmake_minimum_required(VERSION 3.12)

project(Plots VERSION 0.1 LANGUAGES C CXX )

# C++ standard
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)


# Default build type
#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
#endif()

#all sorce
file (GLOB PROJ_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

#glad
include_directories(${PROJECT_SOURCE_DIR}/dep/glad/include)
set (GLAD_SRC ${PROJECT_SOURCE_DIR}/dep/glad/src/glad.c)

#GLM (Didn't want to add this but should shorten development.)
include_directories("C:/Users/Cesar/eclipse-workspace/Plots/dep/glm")

#set (glad_DIR ${PROJECT_SOURCE_DIR}/dep/glad)

#openGL
if(WIN32)
    find_package(OpenGL )
    include_directories("C:/Program Files/glfw/include/")
    link_directories ("C:/Program Files/glfw/lib-vc2022")
else()
    find_package(OpenGL )
    find_package(glfw3 )
endif()



#Free Type
if(WIN32)
    include_directories("C:/Program Files/freeType/include/")
    link_directories ("C:/Program Files/freeType/release_static/vs2015-2022/win64/")
else()
    find_package(Freetype REQUIRED)
endif()



# Sources (adjust paths as needed)
add_executable(${PROJECT_NAME} main.cpp ${GLAD_SRC} ${PROJ_SRC}) 

# Include directories
#target_include_directories( ${PROJECT_NAME}  PRIVATE include)

#in

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL glfw3 freetype)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL glfw Freetype::Freetype)
endif()


add_compile_options(-fsanitize=address -fsanitize=undefined)
add_link_options(-fsanitize=address -fsanitize=undefined)