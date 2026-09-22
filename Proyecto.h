#ifndef PROYECTO_H
#define PROYECTO_H

#include <string>
#include <iostream>
#include "Investigador.h"

// Nodo de la Lista Doble de Proyectos de Investigación
struct NodoProyecto {
    std::string idProyecto;
    std::string nombre;
    double financiamiento;
    int anioInicio;
    int anioFin;
    NodoInvestigador* investigadorResponsable; // Enlace al investigador responsable
    NodoProyecto* siguiente;
    NodoProyecto* anterior;

    NodoProyecto(const std::string& id, const std::string& nom, double fin,
                 int aIni, int aFin, NodoInvestigador* resp)
        : idProyecto(id), nombre(nom), financiamiento(fin),
          anioInicio(aIni), anioFin(aFin), investigadorResponsable(resp),
          siguiente(nullptr), anterior(nullptr) {}
};

// Lista Doble de Proyectos de Investigación
// Requisito: Inserción ordenada por fecha/año de inicio
class ListaProyectos {
private:
    NodoProyecto* cabeza;
    NodoProyecto* cola;
    int tamano;

public:
    ListaProyectos();
    ~ListaProyectos();

    // Operaciones principales
    bool insertarOrdenadoPorAnio(const std::string& id, const std::string& nom, double fin,
                                 int aIni, int aFin, NodoInvestigador* resp);
    NodoProyecto* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNom, double nuevoFin,
                   int nuevoAIni, int nuevoAFin, NodoInvestigador* nuevoResp);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Validaciones y utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoProyecto* getCabeza() const { return cabeza; }
    void liberar();
};

#endif // PROYECTO_H
