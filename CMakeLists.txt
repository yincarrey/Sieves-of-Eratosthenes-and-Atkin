cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Encuentra OpenMP
find_package(OpenMP REQUIRED)

# Configura las opciones de compilación para OpenMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# Configura la carpeta de salida para el ejecutable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/executable)

# Configura la biblioteca
add_library(_header
    src/headers/header.cpp
    src/headers/header.h
)

target_include_directories(_header PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# Configura el ejecutable
add_executable(numerosPrimosParalelo
    src/main.cpp
)

target_link_libraries(numerosPrimosParalelo PUBLIC _header)