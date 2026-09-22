#ifndef UNIVERSIDAD_H
#define UNIVERSIDAD_H

#include <string>
#include <iostream>

// Nodo de la Lista Doble de Universidades
struct NodoUniversidad {
    std::string idUniversidad;
    std::string nombre;
    std::string pais;
    int ranking;
    NodoUniversidad* siguiente;
    NodoUniversidad* anterior;

    NodoUniversidad(const std::string& id, const std::string& nom, const std::string& p, int rank)
        : idUniversidad(id), nombre(nom), pais(p), ranking(rank), siguiente(nullptr), anterior(nullptr) {}
};

// Lista Doble de Universidades
// Requisito: Inserción como guste (implementada al final manteniendo enlaces dobles)
class ListaUniversidades {
private:
    NodoUniversidad* cabeza;
    NodoUniversidad* cola;
    int tamano;

public:
    ListaUniversidades();
    ~ListaUniversidades();

    // Operaciones requeridas
    bool insertar(const std::string& id, const std::string& nom, const std::string& pais, int ranking);
    NodoUniversidad* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNombre, const std::string& nuevoPais, int nuevoRanking);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Utilidades y validaciones
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoUniversidad* getCabeza() const { return cabeza; }
    void liberar();
};

#endif // UNIVERSIDAD_H
