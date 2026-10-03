#pragma once
#include <string>
#include "Investigador.h"
#include "Coautor.h"
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
    ListaCoautores sublistaCoautores;       // Sublista de coautores de esta publicacion
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

    // Auxiliares: mover un nodo sin borrarlo y limpiar citas que apuntan a un nodo
    void desenlazar(NodoPublicacion* nodo);
    void enlazarOrdenado(NodoPublicacion* nodo);
    void anularCitasHacia(NodoPublicacion* objetivo);

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

    // Llena el enlace "publicacion" de cada investigador y de cada revista
    // (apunta a la primera publicacion de la lista circular que les pertenece)
    void actualizarEnlaces(ListaInvestigadores& invs, ListaRevistas& revs) const;

    // Métodos para relaciones de
    void mostrarPublicacionesDeProyecto(const std::string& idProy) const;

    // Metodos para agregar autores a una publicacion
    bool agregarCoautorAPublicacion(const std::string& idPub, NodoInvestigador* investigadorPropietario,
                                    const std::string& idCoautor);

    // Metodos para agregar citas a una publicacion
    bool agregarCitaAPublicacion(const std::string& idPub, const std::string& idCita,
                                 int anioCita, NodoPublicacion* pubCitante, NodoInvestigador* autCitante);

    // Validaciones y utilidades
    static bool esTipoValido(const std::string& t);
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoPublicacion* getCabeza() const { return cabeza; }
    void liberar();
};
