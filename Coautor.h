#ifndef COAUTOR_H
#define COAUTOR_H

#include <string>
#include <iostream>

// Nodo de la Lista Doble de Coautores (sublista dentro de Investigador)
struct NodoCoautor {
    std::string idCoautor;
    std::string nombre;
    std::string universidad;
    int publicacionesConjuntas;
    NodoCoautor* siguiente;
    NodoCoautor* anterior;

    NodoCoautor(const std::string& id, const std::string& nom, const std::string& uni, int pubConj)
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
    bool insertar(const std::string& id, const std::string& nom, const std::string& uni, int pubConj);
    NodoCoautor* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNom, const std::string& nuevaUni, int nuevasPubConj);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoCoautor* getCabeza() const { return cabeza; }
    void liberar();
};

#endif // COAUTOR_H
