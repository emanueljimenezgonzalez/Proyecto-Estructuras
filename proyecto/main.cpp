// ================================================================
// Sistema de Gestion de Produccion Cientifica y Metricas Academicas
// ================================================================

#include <iostream>
#include "Sistema.h"

using namespace std;

int main() {
    std::cout << "================================================================================\n";
    std::cout << "                 INSTITUTO TECNOLOGICO DE COSTA RICA                            \n";
    std::cout << "               CURSO IC2001 - ESTRUCTURAS DE DATOS                              \n";
    std::cout << "                   PROF. LORENA VALERIO SOLIS                                   \n";
    std::cout << "  SISTEMA DE GESTION DE PRODUCCION CIENTIFICA Y METRICAS ACADEMICAS\n";
    std::cout << "================================================================================\n";
    std::cout << "PROYECTO INTEGRADO  \n";
    std::cout << "================================================================================\n\n";

    SistemaAcademico sistema;
    sistema.menuPrincipal();

    return 0;
}
