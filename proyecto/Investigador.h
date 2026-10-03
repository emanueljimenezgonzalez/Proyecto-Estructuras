#pragma once
#include <string>
#include "Universidad.h"
#include "Area.h"
#include "Coautor.h"

struct NodoPublicacion;   // forward declaration

// Nodo de la Lista Simple de Investigadores
struct NodoInvestigador {
    std::string idInvestigador;
    std::string nombreCompleto;
    NodoUniversidad* universidad;  // Enlace a la universidad
    std::string pais;
    NodoArea* area;                // Enlace al area de investigacion
    std::string correo;
    int indiceH;
    ListaCoautores sublistaCoautores; // Sublista doble de coautores
    NodoPublicacion* publicacion;     // Enlace a una publicacion del investigador (1:N)
    NodoInvestigador* siguiente;

    NodoInvestigador(const std::string& id, const std::string& nom,
                     NodoUniversidad* uni, const std::string& p,
                     NodoArea* ar, const std::string& email)
        : idInvestigador(id), nombreCompleto(nom), universidad(uni),
          pais(p), area(ar), correo(email), indiceH(0),
          publicacion(nullptr), siguiente(nullptr) {}
};

// Lista Simple de Investigadores
// Requisito: Inserción al final
class ListaInvestigadores {
private:
    NodoInvestigador* cabeza;
    int tamano;

public:
    ListaInvestigadores();
    ~ListaInvestigadores();

    // Operaciones principales
    bool insertarAlFinal(const std::string& id, const std::string& nom,
                         NodoUniversidad* uni, const std::string& pais,
                         NodoArea* ar, const std::string& email);
    NodoInvestigador* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNombre,
                   NodoUniversidad* nuevaUni, const std::string& nuevoPais,
                   NodoArea* nuevaArea, const std::string& nuevoCorreo);
    bool eliminar(const std::string& id);
    void mostrar() const;
    void mostrarConDetalles() const;

    // Métricas y utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoInvestigador* getCabeza() const { return cabeza; }
    void liberar();
};
