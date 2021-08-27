file(GLOB srcs *.cpp)

if(WIN32)
  set(gl_libs opengl32)
  list(APPEND srcs ${CMAKE_SOURCE_DIR}/assets/res.rc)
endif(WIN32)

if(UNIX)
  message(STATUS "Building for ${CMAKE_SYSTEM}")
  set(gl_libs GL)
endif()

add_executable(${CMAKE_PROJECT_NAME} ${srcs})
target_link_libraries(${CMAKE_PROJECT_NAME} imgui glfw ${gl_libs})