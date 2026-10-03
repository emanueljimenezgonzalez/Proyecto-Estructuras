#pragma once
#include <string>

struct NodoPublicacion;    // forward declarations
struct NodoInvestigador;

// Nodo de la Lista Doble de Citaciones (sublista dentro de Publicación)
struct NodoCitacion {
    std::string idCita;
    int anio;
    NodoPublicacion* publicacionCitante;   // Enlace a la publicacion que cita
    NodoInvestigador* autorCitante;        // Enlace al investigador que realizo la cita
    NodoCitacion* siguiente;
    NodoCitacion* anterior;

    NodoCitacion(const std::string& id, int a, NodoPublicacion* pubCit, NodoInvestigador* autCit)
        : idCita(id), anio(a), publicacionCitante(pubCit), autorCitante(autCit),
          siguiente(nullptr), anterior(nullptr) {}
};

// Lista Doble de Citaciones
// Requisito: Inserción como guste
class ListaCitaciones {
private:
    NodoCitacion* cabeza;
    NodoCitacion* cola;
    int tamano;

public:
    ListaCitaciones();
    ~ListaCitaciones();

    // Operaciones principales
    bool insertar(const std::string& id, int a, NodoPublicacion* pubCit, NodoInvestigador* autCit);
    NodoCitacion* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, int nuevoAnio, NodoPublicacion* nuevaPubCit, NodoInvestigador* nuevoAutCit);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoCitacion* getCabeza() const { return cabeza; }
    void liberar();
};
