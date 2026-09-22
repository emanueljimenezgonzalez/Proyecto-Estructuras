#include <iostream>
#include "Sistema.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // Configurar salida de consola de Windows
    SetConsoleOutputCP(65001);
#endif

    std::cout << "================================================================================\n";
    std::cout << "                 INSTITUTO TECNOLOGICO DE COSTA RICA                            \n";
    std::cout << "               CURSO IC2001 - ESTRUCTURAS DE DATOS                              \n";
    std::cout << "                   PROF. LORENA VALERIO SOLIS                                   \n";
    std::cout << "  SISTEMA DE GESTION DE PRODUCCION CIENTIFICA Y METRICAS ACADEMICAS             \n";
    std::cout << "================================================================================\n";
    std::cout << "MODULO ENFOCADO: PERSONA 3 (PUBLICACIONES, CITACIONES, METRICAS E INTEGRACION)  \n";
    std::cout << "================================================================================\n\n";

    SistemaAcademico sistema;
    sistema.menuPrincipal();

    return 0;
}
