#ifndef SISTEMA_H
#define SISTEMA_H

#include "Area.h"
#include "Universidad.h"
#include "Coautor.h"
#include "Investigador.h"
#include "Revista.h"
#include "Proyecto.h"
#include "Citacion.h"
#include "Publicacion.h"
#include "Metricas.h"
#include "Consultas.h"
#include "Reportes.h"

class SistemaAcademico {
private:
    ListaAreas listaAreas;
    ListaUniversidades listaUniversidades;
    ListaRevistas listaRevistas;
    ListaInvestigadores listaInvestigadores;
    ListaProyectos listaProyectos;
    ListaPublicaciones listaPublicaciones;

public:
    SistemaAcademico();
    ~SistemaAcademico();

    // Carga de datos iniciales (>5 registros por cada una de las 8 listas)
    void precargarDatos();

    // Getters de las listas
    ListaAreas& getAreas() { return listaAreas; }
    ListaUniversidades& getUniversidades() { return listaUniversidades; }
    ListaRevistas& getRevistas() { return listaRevistas; }
    ListaInvestigadores& getInvestigadores() { return listaInvestigadores; }
    ListaProyectos& getProyectos() { return listaProyectos; }
    ListaPublicaciones& getPublicaciones() { return listaPublicaciones; }

    // Módulos interactivos de menús
    void menuPrincipal();
    void menuInvestigadores();
    void menuUniversidades();
    void menuAreas();
    void menuRevistas();
    void menuProyectos();
    void menuPublicaciones();      // Responsabilidad Persona 3
    void menuCitaciones();         // Responsabilidad Persona 3
    void menuMetricas();           // Responsabilidad Persona 3
    void menuConsultas();
    void menuReportes();
    void menuPersona2();           // Módulo integral exclusivo Persona 2 (Revistas y Proyectos)

    // Prueba demostrativa del ejemplo de Índice H = 5 del enunciado oficial
    void ejecutarPruebaEjemploIndiceH();
};

#endif // SISTEMA_H
