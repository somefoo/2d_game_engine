if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror -Wno-unused-private-field")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Og -fsanitize=address")
project(my_game VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB my_game_engine_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
    "../src/*.h"
    "../src/*.cpp"
    "../src/*.hpp"
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
add_executable(my_game main.cpp ${my_game_engine_SRC})

find_package(OpenMP REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)
#find_package(PNG REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#target_link_libraries(my_game PRIVATE OpenMP::OpenMP_CXX ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ${GLEW_LIBRARY} ${SDL2_LIBRARIES})
target_link_libraries(my_game PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${OpenMP_CXX_LIBRARIES} ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ${GLEW_LIBRARY} ${SDL2_LIBRARIES})
