#pragma once
#include <string>

struct NodoUniversidad;   // forward declaration

// Nodo de la Lista Doble de Coautores (sublista dentro de Investigador)
struct NodoCoautor {
    std::string idCoautor;
    std::string nombre;
    NodoUniversidad* universidad;     // Enlace a la universidad (N:1)
    int publicacionesConjuntas;
    NodoCoautor* siguiente;
    NodoCoautor* anterior;

    NodoCoautor(const std::string& id, const std::string& nom, NodoUniversidad* uni, int pubConj)
        : idCoautor(id), nombre(nom), universidad(uni), publicacionesConjuntas(pubConj),
          siguiente(nullptr), anterior(nullptr) {}
};

// Lista Doble de Coautores
// Requisito: Inserción como guste
class ListaCoautores {
private:
    NodoCoautor* cabeza;
    NodoCoautor* cola;
    int tamano;

public:
    ListaCoautores();
    ~ListaCoautores();

    // Operaciones
    bool insertar(const std::string& id, const std::string& nom, NodoUniversidad* uni, int pubConj);
    NodoCoautor* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNom, NodoUniversidad* nuevaUni, int nuevasPubConj);

    // Agrega un coautor existente a esta sublista (crea un nodo con los mismos datos)
    bool agregarCoautorExistente(NodoCoautor* coautor);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoCoautor* getCabeza() const { return cabeza; }
    void liberar();
};
