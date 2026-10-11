cmake_minimum_required(VERSION 3.16)

project(Desafio_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Desafio_2 main.cpp
    udeabook.h udeabook.cpp
    usuario.h usuario.cpp
    matrizadyacencia.h matrizadyacencia.cpp
    lista.h lista.cpp
    foto.h foto.cpp
    fecha.h fecha.cpp
    mensaje.h mensaje.cpp
    album.h album.cpp
    contador.h contador.cpp)

include(GNUInstallDirs)
install(TARGETS Desafio_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
