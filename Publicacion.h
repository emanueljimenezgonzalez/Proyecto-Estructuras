#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <string>
#include <iostream>
#include "Investigador.h"
#include "Revista.h"
#include "Proyecto.h"
#include "Citacion.h"

// Nodo de la Lista Circular de Publicaciones
struct NodoPublicacion {
    std::string idPublicacion;
    std::string titulo;
    int anio;
    std::string tipo; // "Articulo", "Libro", "Conferencia"
    int cantidadCitas;
    std::string doi;
    NodoInvestigador* investigadorPrincipal; // Enlace al investigador principal
    NodoRevista* revista;                   // Enlace a revista (puede ser nullptr)
    NodoProyecto* proyecto;                 // Enlace a proyecto (puede ser nullptr)
    ListaCitaciones sublistaCitaciones;     // Sublista doble de citaciones
    NodoPublicacion* siguiente;             // Puntero circular al siguiente

    NodoPublicacion(const std::string& id, const std::string& tit, int a,
                    const std::string& tip, int citas, const std::string& d,
                    NodoInvestigador* inv, NodoRevista* rev, NodoProyecto* proy)
        : idPublicacion(id), titulo(tit), anio(a), tipo(tip), cantidadCitas(citas),
          doi(d), investigadorPrincipal(inv), revista(rev), proyecto(proy),
          siguiente(nullptr) {}
};

// Lista Circular de Publicaciones
// Requisito: Inserción ordenada por año ascendente
class ListaPublicaciones {
private:
    NodoPublicacion* cabeza;
    int tamano;

public:
    ListaPublicaciones();
    ~ListaPublicaciones();

    // Operaciones principales
    bool insertarOrdenadoPorAnio(const std::string& id, const std::string& tit, int anio,
                                 const std::string& tipo, int citas, const std::string& doi,
                                 NodoInvestigador* inv, NodoRevista* rev, NodoProyecto* proy);
    NodoPublicacion* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoTit, int nuevoAnio,
                   const std::string& nuevoTipo, int nuevasCitas, const std::string& nuevoDoi,
                   NodoInvestigador* nuevoInv, NodoRevista* nuevaRev, NodoProyecto* nuevoProy);
    bool eliminar(const std::string& id);
    void mostrar() const;
    void mostrarConDetalles() const;

    // Métodos para relaciones de Persona 2
    void mostrarPublicacionesDeProyecto(const std::string& idProy) const;

    // Métodos para agregar citas a una publicación
    bool agregarCitaAPublicacion(const std::string& idPub, const std::string& idCita,
                                 int anioCita, const std::string& pubCit, const std::string& autCit);

    // Validaciones y utilidades
    static bool esTipoValido(const std::string& t);
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoPublicacion* getCabeza() const { return cabeza; }
    void liberar();
};

#endif // PUBLICACION_H
