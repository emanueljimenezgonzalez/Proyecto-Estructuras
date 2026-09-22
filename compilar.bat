@echo off
echo =======================================================
echo Compilando Sistema de Gestion de Produccion Cientifica
echo Curso IC2001 - Estructuras de Datos (TEC)
echo =======================================================

g++ -std=c++11 -Wall -Wextra -O2 -o sistema_academico.exe main.cpp Sistema.cpp Publicacion.cpp Citacion.cpp Metricas.cpp Consultas.cpp Reportes.cpp Investigador.cpp Coautor.cpp Revista.cpp Proyecto.cpp Universidad.cpp Area.cpp

if %ERRORLEVEL% EQU 0 (
    echo [EXITO] Compilacion completada sin errores.
    echo Se ha generado el ejecutable: sistema_academico.exe
    echo Ejecutando sistema...
    echo.
    sistema_academico.exe
) else (
    echo [ERROR] Hubo problemas durante la compilacion.
)
pause
