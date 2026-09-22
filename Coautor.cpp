#include "Coautor.h"
#include <iostream>
#include <iomanip>

ListaCoautores::ListaCoautores() : cabeza(nullptr), cola(nullptr), tamano(0) {}

ListaCoautores::~ListaCoautores() {
    liberar();
}

void ListaCoautores::liberar() {
    NodoCoautor* actual = cabeza;
    while (actual != nullptr) {
        NodoCoautor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

bool ListaCoautores::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaCoautores::insertar(const std::string& id, const std::string& nom, const std::string& uni, int pubConj) {
    if (id.empty() || nom.empty()) {
        std::cout << "    [ERROR] ID y nombre de coautor son requeridos.\n";
        return false;
    }
    if (existeId(id)) {
        std::cout << "    [ERROR] Ya existe un coautor con ID: " << id << "\n";
        return false;
    }
    if (pubConj < 0) {
        pubConj = 0;
    }

    NodoCoautor* nuevo = new NodoCoautor(id, nom, uni, pubConj);
    if (cabeza == nullptr) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
    tamano++;
    return true;
}

NodoCoautor* ListaCoautores::buscarPorId(const std::string& id) const {
    NodoCoautor* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idCoautor == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaCoautores::modificar(const std::string& id, const std::string& nuevoNom, const std::string& nuevaUni, int nuevasPubConj) {
    NodoCoautor* nodo = buscarPorId(id);
    if (nodo == nullptr) return false;
    if (!nuevoNom.empty()) nodo->nombre = nuevoNom;
    if (!nuevaUni.empty()) nodo->universidad = nuevaUni;
    if (nuevasPubConj >= 0) nodo->publicacionesConjuntas = nuevasPubConj;
    return true;
}

bool ListaCoautores::eliminar(const std::string& id) {
    NodoCoautor* nodo = buscarPorId(id);
    if (nodo == nullptr) return false;

    if (nodo == cabeza && nodo == cola) {
        cabeza = cola = nullptr;
    } else if (nodo == cabeza) {
        cabeza = cabeza->siguiente;
        cabeza->anterior = nullptr;
    } else if (nodo == cola) {
        cola = cola->anterior;
        cola->siguiente = nullptr;
    } else {
        nodo->anterior->siguiente = nodo->siguiente;
        nodo->siguiente->anterior = nodo->anterior;
    }

    delete nodo;
    tamano--;
    return true;
}

void ListaCoautores::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "    (Sin coautores registrados)\n";
        return;
    }

    NodoCoautor* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "    * [" << actual->idCoautor << "] " << actual->nombre
                  << " (" << actual->universidad << ") - Pub. conjuntas: "
                  << actual->publicacionesConjuntas << "\n";
        actual = actual->siguiente;
    }
}
