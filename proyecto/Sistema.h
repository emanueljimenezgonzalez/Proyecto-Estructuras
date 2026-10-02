#pragma once
#include "Area.h"
#include "Universidad.h"
#include "Revista.h"
#include "Investigador.h"
#include "Proyecto.h"
#include "Publicacion.h"

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
    void menuPublicaciones();
    void menuCitaciones();
    void menuMetricas();
    void menuConsultas();
    void menuReportes();
    void menu();

    // Prueba demostrativa del ejemplo de Índice H = 5 del enunciado oficial
    void ejecutarPruebaEjemploIndiceH();
};
