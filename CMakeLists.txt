cmake_minimum_required(VERSION 3.26)
project(CRUD2_0_IP C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CRUD2_0_IP
        atendimentos.c
        atendimentos.h
        main.c
        pacientes.c
        pacientes.h
        util.c
        util.h)
