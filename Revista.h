#ifndef REVISTA_H
#define REVISTA_H

#include <string>
#include <iostream>

// Nodo de la Lista Simple de Revistas Científicas
struct NodoRevista {
    std::string idRevista;
    std::string nombre;
    std::string editorial;
    std::string pais;
    double factorImpacto;
    std::string cuartil; // Q1, Q2, Q3, Q4
    NodoRevista* siguiente;

    NodoRevista(const std::string& id, const std::string& nom, const std::string& ed,
                const std::string& p, double fi, const std::string& q)
        : idRevista(id), nombre(nom), editorial(ed), pais(p),
          factorImpacto(fi), cuartil(q), siguiente(nullptr) {}
};

// Lista Simple de Revistas Científicas
// Requisito: Inserción ordenada por nombre
class ListaRevistas {
private:
    NodoRevista* cabeza;
    int tamano;

public:
    ListaRevistas();
    ~ListaRevistas();

    // Operaciones principales
    bool insertarOrdenado(const std::string& id, const std::string& nom, const std::string& ed,
                          const std::string& p, double fi, const std::string& q);
    NodoRevista* buscarPorId(const std::string& id) const;
    NodoRevista* buscarPorNombre(const std::string& nom) const;
    bool modificar(const std::string& id, const std::string& nuevoNom, const std::string& nuevaEd,
                   const std::string& nuevoPais, double nuevoFI, const std::string& nuevoCuartil);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Validaciones y utilidades
    static bool esCuartilValido(const std::string& q);
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoRevista* getCabeza() const { return cabeza; }
    void liberar();
};

#endif // REVISTA_H
