#ifndef AREA_H
#define AREA_H

#include <string>
#include <iostream>

// Nodo de la Lista Simple de Áreas de Investigación
struct NodoArea {
    std::string idArea;
    std::string nombre;
    std::string descripcion;
    NodoArea* siguiente;

    NodoArea(const std::string& id, const std::string& nom, const std::string& desc)
        : idArea(id), nombre(nom), descripcion(desc), siguiente(nullptr) {}
};

// Lista Simple de Áreas de Investigación
// Requisito: Inserción al final
class ListaAreas {
private:
    NodoArea* cabeza;
    int tamano;

public:
    ListaAreas();
    ~ListaAreas();

    // Operaciones requeridas
    bool insertarAlFinal(const std::string& id, const std::string& nom, const std::string& desc);
    NodoArea* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNombre, const std::string& nuevaDesc);
    bool eliminar(const std::string& id);
    void mostrar() const;
    
    // Validaciones y utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoArea* getCabeza() const { return cabeza; }
    void liberar();
};

#endif // AREA_H
