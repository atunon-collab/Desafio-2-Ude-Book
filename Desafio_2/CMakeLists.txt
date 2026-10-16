cmake_minimum_required(VERSION 3.16)

project(Desafio_2 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Desafio_2 main.cpp
    udeabook.h udeabook.cpp
    usuario.h usuario.cpp
    matrizadyacencia.h matrizadyacencia.cpp
    lista.h
    foto.h foto.cpp
    fecha.h fecha.cpp
    mensaje.h mensaje.cpp
    album.h album.cpp
    contador.h contador.cpp)

# Ruta del archivo de datos para que funcione desde Qt Creator
target_compile_definitions(Desafio_2 PRIVATE RUTA_DATOS="${CMAKE_CURRENT_SOURCE_DIR}/datos/udeabook.txt")

include(GNUInstallDirs)
install(TARGETS Desafio_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
