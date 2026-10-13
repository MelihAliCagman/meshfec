cmake_minimum_required(VERSION 3.16)
project(meshfec LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # VS Code IntelliSense için

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Kütüphanemiz header-only: .hpp dosyaları include/meshfec/ altında.
add_library(meshfec INTERFACE)
target_include_directories(meshfec INTERFACE include)
target_compile_options(meshfec INTERFACE -Wall -Wextra -Wpedantic)

# Her .cpp dosyası ayrı bir program olur (dosya adı = program adı).
# Dosya BOŞSA (henüz yazılmadıysa) atlanır; doldurup kaydedince bir sonraki
# derlemede otomatik olarak dahil edilir.
function(meshfec_add_program path is_test)
  set(full ${CMAKE_CURRENT_SOURCE_DIR}/${path})
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${full})
  file(SIZE ${full} size)
  if(size EQUAL 0)
    message(STATUS "atlandi (bos): ${path}")
    return()
  endif()
  get_filename_component(name ${path} NAME_WE)
  add_executable(${name} ${full})
  target_link_libraries(${name} PRIVATE meshfec)
  if(is_test)
    add_test(NAME ${name} COMMAND ${name})
  endif()
endfunction()

enable_testing()

file(GLOB TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS tests/test_*.cpp)
foreach(f ${TEST_FILES})
  meshfec_add_program(${f} TRUE)
endforeach()

file(GLOB APP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS apps/*.cpp)
foreach(f ${APP_FILES})
  meshfec_add_program(${f} FALSE)
endforeach()
